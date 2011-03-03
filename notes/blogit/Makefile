RAWTEXFILES := $(shell ls *.tex)

#PHY450_PS3_2 := relElectroDynProblemSet3TwoInternals.tex
PHY450_PS4_2 := relElectroDynProblemSet4TwoInternals.tex

#INCOMPLETE += relativisticElectrodynamicsL16.tex
#INCOMPLETE += $(PHY450_PS3_2)
INCOMPLETE += $(PHY450_PS4_2)

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
ORIG_FILES += ../otherbook/triangleLaw.png
ORIG_FILES += ../otherbook/rotateMinusOne.png
ORIG_FILES += ../gabook/parallelogramArea.png

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
	perl ../make_pdflatex $<

clean :: mostlyclean localclean

mostlyclean :: 
	rm -f *.ps *.dvi *.pdf *.aux *.log *.bbl *.blg *.brf *.toc *.stackdump

localclean ::
	rm -f $(LOCAL_FILES)

#relElectroDynProblemSet3.pdf : $(PHY450_PS3_2)
#relElectroDynProblemSet3_2.pdf: $(PHY450_PS3_2)

relElectroDynProblemSet4.pdf : $(PHY450_PS4_2)
relElectroDynProblemSet4_2.pdf: $(PHY450_PS4_2)
