#!/usr/bin/env python3
"""
Ollama query script with persistent conversation history (context caching).
Uses the modern /api/chat endpoint.
"""

import requests
import json
import sys
import os
import argparse
import re
from pathlib import Path

# Default settings
#DEFAULT_MODEL = 'qwen3.5:122b'
DEFAULT_MODEL = 'qwen3.6:35b'
CACHE_FILE = ''

def load_cache(cache_path: str):
    if os.path.exists(cache_path):
        try:
            with open(cache_path, 'r', encoding='utf-8') as f:
                return json.load(f)
        except Exception as e:
            print(f"Warning: Could not load cache: {e}")
    return []

def save_cache(cache_path: str, messages: list):
    try:
        with open(cache_path, 'w', encoding='utf-8') as f:
            json.dump(messages, f, ensure_ascii=False, indent=2)
    except Exception as e:
        print(f"Warning: Could not save cache: {e}")

def query_ollama(model: str, messages: list, num_ctx: int = 131072):
    """Send request using the modern /api/chat endpoint"""
    payload = {
        "model": model,
        "messages": messages,
        "stream": False,
        "options": {
            "num_ctx": num_ctx,      # Large context for your M5 Max
            "temperature": 0.7,
        }
    }

    try:
        response = requests.post(
            'http://localhost:11434/api/chat',
            json=payload,
            timeout=300
        )
        response.raise_for_status()
        return response.json()
    except requests.exceptions.RequestException as e:
        print(f"Error communicating with Ollama: {e}")
        sys.exit(1)

def main():
    global CACHE_FILE

    parser = argparse.ArgumentParser(description="Query Ollama with persistent context caching.")
    parser.add_argument('--clean', action='store_true', help="Start with empty context (no history).")
    parser.add_argument('--model', type=str, default=DEFAULT_MODEL, help="Model to use.")
    parser.add_argument('--cache', type=str, default='context', help="Cache name component (default: context).")
    parser.add_argument('--query', type=str, help="Path to a file containing the query (non-interactive mode).")
    parser.add_argument('--system', type=str, default="", help="Optional system prompt.")
    args = parser.parse_args()

    model = args.model
    print(f"Using model: {model}")

    # Set cache file path
    cache_name = args.cache
    CACHE_FILE = os.path.expanduser(f'~/.llmq.{cache_name}.{model.replace(":", "_")}.json')
    print(f"Context cache file: {CACHE_FILE}")

    # Load previous messages or start fresh
    if args.clean:
        messages = []
        print("Starting with clean (empty) context.")
    else:
        messages = load_cache(CACHE_FILE)

    # Add system prompt once at the beginning if provided and not already present
    if args.system and (not messages or messages[0].get("role") != "system"):
        messages.insert(0, {"role": "system", "content": args.system})

    while True:
        if args.query:
            try:
                prompt = Path(args.query).read_text(encoding='utf-8').strip()
            except Exception as e:
                print(f"Error reading query file: {e}")
                sys.exit(1)
        else:
            prompt = input("\nEnter your query (or 'exit'/'quit' to stop): ").strip()
            if re.match(r'^(exit|quit)$', prompt.lower()):
                print("Exiting...")
                break

        if not prompt:
            if args.query:
                break
            continue

        # Add user message
        messages.append({"role": "user", "content": prompt})

        # Query the model
        response = query_ollama(model, messages)

        # Extract assistant reply
        assistant_message = response.get('message', {})
        reply = assistant_message.get('content', 'No response received.')

        print(f"\nResponse:\n{reply}\n")

        # Add assistant message to history
        messages.append({"role": "assistant", "content": reply})

        # Save updated history
        save_cache(CACHE_FILE, messages)

        # Non-interactive mode: run once and exit
        if args.query:
            break

if __name__ == "__main__":
    main()
