I'm using MikTex on windows 7 to build this doc, and some hand holding was required to get all the 
packages and fonts.

1) expl3.sty not found.
   Solution: run MikTex update manager (admin), and refresh the packages.  This has to be done twice, 
   once for the package list, and once for the rest of the packages.  After doing this expl3 will be
   found.

2) font errors:
   (see the transcript file for additional information)
   !pdfTeX error: pdflatex.exe (file fvmr8r): Font fvmr8r at 558 not found
    ==> Fatal error occurred, no output PDF file produced!

See Marco's answer:
   http://tex.stackexchange.com/questions/53808/miktex-font-ccicons-at-600-not-found
