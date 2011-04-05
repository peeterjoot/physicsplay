RAWTEXFILES := $(shell ls *.tex)

#PHY450_PS3_2 := relElectroDynProblemSet3TwoInternals.tex
#PHY450_PS4_2 := relElectroDynProblemSet4TwoInternals.tex
PHY450_PS5_1 := relElectroDynProblemSet5OneInternals.tex
PHY450_PS6_1 := relElectroDynProblemSet6OneInternals.tex

#INCOMPLETE += $(PHY450_PS3_2)
#INCOMPLETE += $(PHY450_PS4_2)
INCOMPLETE += $(PHY450_PS5_1)
INCOMPLETE += $(PHY450_PS6_1)
INCOMPLETE += relElectroDynProblemSet3_2.tex
INCOMPLETE += relElectroDynProblemSet4_2.tex
# temp.  just to speed up the build.
#INCOMPLETE += relElectroDynProblemSet6.tex
#INCOMPLETE += relElectroDynProblemSet6_1.tex

# need phy450ps5P1Q7.png:
#INCOMPLETE += relElectroDynProblemSet5.tex
#INCOMPLETE += relElectroDynProblemSet5_1.tex

# in progress.  Lots to do (took notes on paper).
INCOMPLETE += relativisticElectrodynamicsL23.tex
INCOMPLETE += relativisticElectrodynamicsL26.tex

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

#relElectroDynProblemSet4.pdf : $(PHY450_PS4_2)
#relElectroDynProblemSet4_2.pdf: $(PHY450_PS4_2)

relElectroDynProblemSet5.pdf : $(PHY450_PS5_1)
relElectroDynProblemSet5_1.pdf: $(PHY450_PS5_1)

relElectroDynProblemSet6.pdf : $(PHY450_PS6_1)
relElectroDynProblemSet6_1.pdf: $(PHY450_PS6_1)
