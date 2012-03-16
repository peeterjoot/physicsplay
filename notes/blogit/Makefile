RAWTEXFILES := $(shell ls *.tex)
#INCOMPLETE += 
TEXFILES := $(filter-out $(INCOMPLETE), $(RAWTEXFILES)) 

PDFS := $(TEXFILES:.tex=.pdf)

# logically symlinks, but MikTex doesn't like those:
ORIG_FILES += ../abbrvurl.bst
ORIG_FILES += ../alphaurl.bst
ORIG_FILES += ../eliblog.cls 
ORIG_FILES += ../eliblogwidescreen.cls 
ORIG_FILES += ../myrefs.bib 
ORIG_FILES += ../plainurl.bst
ORIG_FILES += ../unsrturl.bst

# for gaBasics:
#ORIG_FILES += ../phy456/qmTwoL22fig5.png
ORIG_FILES += ../otherbook/triangleLaw.png
ORIG_FILES += ../otherbook/rotateMinusOne.png
ORIG_FILES += ../gabook/parallelogramArea.png
#ORIG_FILES += ../phy454/continuumL2fig1.png
#ORIG_FILES += ../phy454/continuumL2fig2.png
#ORIG_FILES += ../phy454/continuumL2fig3.png
#ORIG_FILES += ../phy454/continuumL2fig4.png
#ORIG_FILES += ../phy454/continuumL2fig5.png
#ORIG_FILES += ../phy454/continuumProblemSet1Q2fig1.png
#ORIG_FILES += ../phy454/twoLayerInclinedFlowFig1.png
#ORIG_FILES += ../phy454/continuumL13Fig14.png
#ORIG_FILES += ../phy454/continuumL13Fig13.png
ORIG_FILES += ../phy454/continuumProblemSet2Fig1r2.pdf
ORIG_FILES += ../phy454/continuumProblemSet2Fig1r2.pdf_tex
ORIG_FILES += ../phy454/continuumProblemSet2Fig2r2.pdf
ORIG_FILES += ../phy454/continuumProblemSet2Fig2r2.pdf_tex
ORIG_FILES += ../phy454/continuumProblemSet2Fig3.png
ORIG_FILES += ../phy454/continuumProblemSet2Fig4.png
ORIG_FILES += ../phy454/continuumProblemSet2Fig5.png

LOCAL_FILES := $(notdir $(ORIG_FILES))

all :: $(LOCAL_FILES) $(PDFS)
#all :: ftMaxVacuum.pdf

$(PDFS) : $(LOCAL_FILES)

local : $(LOCAL_FILES)

$(LOCAL_FILES) : 
	cp $(filter %$@, $(ORIG_FILES)) $@

gaBasics.pdf : gaBasics.tex

# gaBasics.doc is currently my source for this document:
#
#gaBasics.tex : gaBasics.txt
#	./wordToTex < gaBasics.txt > gaBasics.tex

%.pdf : %.tex
	mkdir -p ./.revinfo/
	~/bin/mkRevInfo > ./.revinfo/lastCommit.tex
	perl ../make_pdflatex $<

clean :: mostlyclean localclean

mostlyclean :: 
	rm -f *.ps *.dvi $(PDFS) *.aux *.log *.bbl *.blg *.brf *.toc *.stackdump *.bib

localclean ::
	rm -f $(LOCAL_FILES)
