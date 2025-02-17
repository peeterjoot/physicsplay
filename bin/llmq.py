#! /usr/bin/env python3

# the pip3 requests module below depends on a virtual environment.  Run this to enter that environment:
#
# cd && . .venv/bin/activate
#

import requests
import json
import sys
import os
import argparse
import re
from pathlib import Path

#MODEL = 'mixtral'
MODEL = 'llama2'
CACHE_FILE = ''

def load_cache():
    if os.path.exists(CACHE_FILE):
        with open(CACHE_FILE, 'r') as f:
            return json.load(f)
    return []

def save_cache(context):
    with open(CACHE_FILE, 'w') as f:
        json.dump(context, f)

def query_ollama(prompt, context):
    response = requests.post(
        'http://localhost:11434/api/generate',
        json={'model': MODEL, 'prompt': prompt, 'context': context, 'stream': False}
    ).json()

    return response

def main():
    global MODEL, CACHE_FILE

    # Set up argument parser
    parser = argparse.ArgumentParser(description="Query the Ollama Mixtral LLM model.")
    parser.add_argument('--clean', action='store_true', help="Start with an empty context list (no cache).")
    parser.add_argument('--model', type=str, default=MODEL, help="Specify an alternative model.")
    parser.add_argument('--cache', type=str, default='context_cache', help="context cache path component.")
    parser.add_argument('--query', type=str, default='', help="multiline query in a file")

    args = parser.parse_args()

    MODEL = args.model
    print(f"Using model: {MODEL}")

    cache = args.cache;
    CACHE_FILE = os.path.expanduser(f'~/.llmq.{cache}.{MODEL}.json')
    print(f"Context cache file: {CACHE_FILE}")

    # Initialize context based on command-line options
    if args.clean:
        context = []
    else:
        context = load_cache()

    while True:
        if args.query:
            prompt = Path(args.query).read_text().strip()
        else:
            # Read input from stdin (interactive prompt)
            prompt = input("Enter your query: ")

            # Check if the prompt matches exit or quit
            if re.match(r'^(exit|quit)$', prompt.lower()):
                print("Exiting...")
                break

        # Query the model and get the response
        response = query_ollama(prompt, context)
        rr = response.get('response', 'No response key in API output')
        print(f"Response: {rr}")

        # Update context (for context propagation)
        context = response.get('context', [])
        save_cache(context)

        if args.query:
            break

if __name__ == "__main__":
    main()

# vim: et ts=4 sw=4
