#!/usr/bin/env python3

# forked from thethe.ph: search for _unlocked in a PDF.

import re
import sys
import io

import pdftotext    # requires installing poppler and pdftotext

# macos:
# brew install poppler
# pip3 install python-poppler
# pip3 install pdftotext

tandem_str = r"_unlocked"
tandem_re = re.compile(tandem_str)

def lines_of_input(filenames):
    for filename in filenames:
        with open(filename, "rb") as file:
            pdf = pdftotext.PDF(file)
            for page in pdf:
                for line in io.StringIO(page):
                    yield filename,line

for filename,line in lines_of_input(sys.argv[1:]):
        if tandem_re.search(line) is not None:
            print(filename,":",line.strip())
