RAWTEXFILES := $(shell ls *.tex)
#INCOMPLETE += qmTwoL8fig0FrequenciesAbsorbtionAndEmission.tex
INCOMPLETE += qmTwoL15halfAngle.tex
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

#ORIG_FILES += ../phy356/gridSummation.png
# for gaBasics:
ORIG_FILES += ../otherbook/triangleLaw.png
ORIG_FILES += ../otherbook/rotateMinusOne.png
ORIG_FILES += ../gabook/parallelogramArea.png

#ORIG_FILES += ../phy456/expMinusBetsAbsX.png
#ORIG_FILES += ../phy456/expMinusBetsAbsXfirstOrderFitting.png
#ORIG_FILES += ../phy456/expMinusBetsAbsXtenthOrderFitting.png
#ORIG_FILES += ../phy456/stepFunction.png
#ORIG_FILES += ../phy456/gaussianWavePacket.png
#ORIG_FILES += ../phy456/FTgaussianWavePacket.png
#ORIG_FILES += ../phy456/suddenStepHamiltonian.png
#ORIG_FILES += ../phy456/suddenHamiltonianPertubationHO.png
#ORIG_FILES += ../phy456/qmTwoL8fig0FrequenciesAbsorbtionAndEmission.pdf
#ORIG_FILES += ../phy456/qmTwoL8fig0FrequenciesAbsorbtionAndEmission.pdf_tex
#ORIG_FILES += ../phy456/unitStepSine.png


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
	rm -f *.ps *.dvi $(PDFS) *.aux *.log *.bbl *.blg *.brf *.toc *.stackdump *.bib

localclean ::
	rm -f $(LOCAL_FILES)
