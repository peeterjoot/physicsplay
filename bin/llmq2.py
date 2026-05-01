#!/usr/bin/env python3
"""
Ollama query script with persistent conversation history.
--query paths are now resolved relative to current working directory.
"""

import requests
import json
import sys
import os
import argparse
import re
from pathlib import Path

DEFAULT_MODEL = 'qwen3.6:35b'

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

def query_ollama(model: str, messages: list, num_ctx: int = 65536):
    payload = {
        "model": model,
        "messages": messages,
        "stream": False,
        "options": {
            "num_ctx": num_ctx,
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
    parser = argparse.ArgumentParser(description="Query Ollama with persistent context.")
    parser.add_argument('--clean', action='store_true', help="Start with empty context.")
    parser.add_argument('--model', type=str, default=DEFAULT_MODEL, help="Model to use.")
    parser.add_argument('--cache', type=str, default='context', help="Cache name component.")
    parser.add_argument('--query', type=str, help="Path to query file (relative to current directory).")
    parser.add_argument('--system', type=str, default="", help="Optional system prompt.")
    args = parser.parse_args()

    model = args.model
    print(f"Using model: {model}")

    cache_file = os.path.expanduser(f'~/.llmq.{args.cache}.{model.replace(":", "_")}.json')
    print(f"Context cache file: {cache_file}")

    # Load history
    if args.clean:
        messages = []
        print("Starting with clean context.")
    else:
        messages = load_cache(cache_file)

    # Add system prompt if provided
    if args.system and (not messages or messages[0].get("role") != "system"):
        messages.insert(0, {"role": "system", "content": args.system})

    while True:
        if args.query:
            query_path = Path(args.query)
            # If user gave a relative path, it stays relative to cwd (default behavior)
            # No extra script_dir logic

            try:
                prompt = query_path.read_text(encoding='utf-8').strip()
                print(f"Loaded query from: {query_path.resolve()}")
            except FileNotFoundError:
                print(f"Error: Query file not found: {query_path}")
                print(f"Current working directory: {Path.cwd()}")
                sys.exit(1)
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

        messages.append({"role": "user", "content": prompt})

        print("Querying model...")
        response = query_ollama(model, messages)

        reply = response.get('message', {}).get('content', 'No response received.')
        print(f"\nResponse:\n{reply}\n")

        messages.append({"role": "assistant", "content": reply})
        save_cache(cache_file, messages)

        if args.query:
            break

if __name__ == "__main__":
    main()
