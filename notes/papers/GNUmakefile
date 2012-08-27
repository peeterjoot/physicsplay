#
# could consider moving: ../nonga/multiPendulumSphericalMatrix.tex here too.
#
THISDIR := papers

# <modified from ../make.vars>
SOURCE_DIRS += .

#GENERATED_SOURCES += currentBookCopyright.tex

# ./ in these due to a bug in the .gitignore generation rule.
COPIED_FILES += ./peeters_macros.sty
COPIED_FILES += ./peeters_layout.sty
COPIED_FILES += ./Bibliography.bib

GENERATED_PDFS += gramSchmidtLorentz.pdf
GENERATED_PDFS += relwave.pdf

CLEAN_TARGETS += *.ilg *.ind *.idx *.ps *.dvi *.log *.aux *.bbl *.blg *.lof *.log *.lot *.out *.toc *.synctex.gz *.stackdump *.brf

DEPENDENCYEXTENSIONS += mp4 pdf_tex png tex sty

# </modified from ../make.vars>

all :: $(GENERATED_PDFS)

$(GENERATED_PDFS) :: $(JUSTBOOKDEPENDENCIES) $(LOCAL_FILES) $(GENERATED_SOURCES) $(COPIED_FILES) $(LOCAL_COPIED_FILES)

include ../make.rules
