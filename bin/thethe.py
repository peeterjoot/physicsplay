#!/usr/bin/env python3

# from https://gasstationwithoutpumps.wordpress.com/2020/09/09/checked-tandem-duplicate-words-in-book/

import re
import sys
import io

import pdftotext	# requires installing poppler and pdftotext

# macos:
# brew install poppler
# pip3 install python-poppler
# pip3 install pdftotext

tandem_str = r"\b(\S+\b)\s+\b\1\b"
tandem_re = re.compile(tandem_str,re.IGNORECASE)

def lines_of_input(filenames):
    if not filenames:
        for line in sys.stdin:
            yield "--stdin",line
    else:
        for filename in filenames:
            if filename.endswith(".pdf"):
            	with open(filename, "rb") as file:
                    pdf = pdftotext.PDF(file)
                    for page in pdf:
                        for line in io.StringIO(page):
                            yield filename,line
            else:
                with open(filename, 'r') as file:
                    for line in file:
                        yield filename,line


for filename,line in lines_of_input(sys.argv[1:]):
#        print("DEBUG:", filename, line, file=sys.stderr)
        if tandem_re.search(line) is not None:
            print(filename,":",line.strip())
