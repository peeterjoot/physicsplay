RAWTEXFILES := $(shell ls *.tex)
INCOMPLETE += motionOfFreeTop.tex
INCOMPLETE += xx.tex
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
ORIG_FILES += ../phy454/couetteFlowFig1.png
ORIG_FILES += ../phy454/couetteFlowFig2.png
ORIG_FILES += ../phy454/couetteFlowFig3.png
ORIG_FILES += ../phy454/couetteFlowFig4.png
ORIG_FILES += ../phy454/couetteFlowFig5.png
ORIG_FILES += ../phy454/couetteFlowFig6.mp4
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
#ORIG_FILES += ../phy454/continuumProblemSet2Fig6mu1Gtmu2.png
#ORIG_FILES += ../phy454/continuumProblemSet2Fig6mu2Gtmu1.png
#ORIG_FILES += ../phy454/continuumProblemSet2Fig1r2.pdf
#ORIG_FILES += ../phy454/continuumProblemSet2Fig1r2.pdf_tex
#ORIG_FILES += ../phy454/continuumProblemSet2Fig2r2.pdf
#ORIG_FILES += ../phy454/continuumProblemSet2Fig2r2.pdf_tex
#ORIG_FILES += ../phy454/continuumProblemSet2Fig3.png
#ORIG_FILES += ../phy454/continuumProblemSet2Fig4.png
#ORIG_FILES += ../phy454/continuumProblemSet2Fig5.png
#ORIG_FILES += ../phy454/inclinedFlowWithoutConstantHeightAssumptionFig1.png
#ORIG_FILES += ../phy454/inclinedFlowWithoutConstantHeightAssumptionFig2.pdf
#ORIG_FILES += ../phy454/inclinedFlowWithoutConstantHeightAssumptionFig2.pdf_tex
#ORIG_FILES += ../phy454/inclinedFlowWithoutConstantHeightAssumptionFig3.pdf
#ORIG_FILES += ../phy454/inclinedFlowWithoutConstantHeightAssumptionFig3.pdf_tex
#ORIG_FILES += ../gabook/gaQuickIntroFig1.pdf
#ORIG_FILES += ../gabook/gaQuickIntroFig1.pdf_tex
#ORIG_FILES += ../gabook/gaQuickIntroFig2.pdf
#ORIG_FILES += ../gabook/gaQuickIntroFig2.pdf_tex
#ORIG_FILES += ../phy454/animatedTwoLayerFlowMu2GreaterThanMu1.avi
#ORIG_FILES += ../phy454/animatedTwoLayerFlowMu1GreaterThanMu2.avi
#ORIG_FILES += ../phy454/channelFlowWithStepPressureGradientTimeEvolution.wmv
#ORIG_FILES += ../strobe/StrobeMediaPlayback.swf
#VIDEO += animatedTwoLayerFlowMu1GreaterThanMu2.mp4

LOCAL_FILES := $(notdir $(ORIG_FILES))

all :: $(LOCAL_FILES) $(PDFS)
#all :: ftMaxVacuum.pdf

video: $(VIDEO)

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

%.mp4 : %.avi
	/cygdrive/c/Temp/ffmpeg/bin/ffmpeg -i $< -vcodec libx264 $@

clean :: mostlyclean localclean

mostlyclean :: 
	rm -f *.ps *.dvi $(PDFS) *.aux *.log *.bbl *.blg *.brf *.toc *.stackdump *.bib

localclean ::
	rm -f $(LOCAL_FILES)
