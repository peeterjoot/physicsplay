#
# could consider moving: ../nonga/multiPendulumSphericalMatrix.tex here too.
#
THISDIR := phy356

#include ../make.vars
SOURCE_DIRS += .

DEPENDENCYEXTENSIONS += mp4 pdf_tex png tex sty

GENERATED_SOURCES += currentBookCopyright.tex

# ./ in these due to a bug in the .gitignore generation rule.
COPIED_FILES += ./peeters_macros.sty
COPIED_FILES += ./peeters_layout.sty
COPIED_FILES += ./Bibliography.bib
COPIED_FILES += ./myrefs.bib

MAIN_TARGETS += ./myrefs.bib
GENERATED_PDFS += gramSchmidtLorentz.pdf
GENERATED_PDFS += relwave.pdf

CLEAN_TARGETS += *.ilg *.ind *.idx *.ps *.dvi *.log *.aux *.bbl *.blg *.lof *.log *.lot *.out *.toc *.synctex.gz *.stackdump *.brf

include ../make.rules
