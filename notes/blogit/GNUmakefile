THISDIR := blogit

RAWTEXFILES := $(shell ls *.tex)
INCOMPLETE += motionOfFreeTop.tex

# these may not all be incomplete, but I don't want to build them right now:
INCOMPLETE += pp.tex
INCOMPLETE += desaiCh24.tex
INCOMPLETE += dotBlade.tex
INCOMPLETE += gaBasics.tex
INCOMPLETE += gaMintro.tex
INCOMPLETE += maxwellsFromGA.tex
INCOMPLETE += parallelAxisTheorem.tex
INCOMPLETE += pipeFlowConstPressureGradient.tex
INCOMPLETE += qmTwoExamReflection.tex
INCOMPLETE += qmTwoR1.tex
INCOMPLETE += qmTwoR5.tex

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
ORIG_FILES += ../classicthesis.mine/mycommon.sty

# for gaBasics:
ORIG_FILES += ../phy454/figures/couetteFlowFig1.png
ORIG_FILES += ../phy454/figures/couetteFlowFig2.png
ORIG_FILES += ../phy454/figures/couetteFlowFig3.png
ORIG_FILES += ../phy454/figures/couetteFlowFig4.png
ORIG_FILES += ../phy454/figures/couetteFlowFig5.png
ORIG_FILES += ../phy454/figures/couetteFlowFig6.mp4
#ORIG_FILES += ../phy456/qmTwoL22fig5.png
ORIG_FILES += ../otherbook/triangleLaw.png
ORIG_FILES += ../otherbook/rotateMinusOne.png
ORIG_FILES += ../gabook/parallelogramArea.png
#ORIG_FILES += ../phy454/figures/continuumL2fig1.png
#ORIG_FILES += ../phy454/figures/continuumL2fig2.png
#ORIG_FILES += ../phy454/figures/continuumL2fig3.png
#ORIG_FILES += ../phy454/figures/continuumL2fig4.png
#ORIG_FILES += ../phy454/figures/continuumL2fig5.png
#ORIG_FILES += ../phy454/figures/continuumProblemSet1Q2fig1.png
#ORIG_FILES += ../phy454/figures/twoLayerInclinedFlowFig1.png
#ORIG_FILES += ../phy454/figures/continuumL13Fig14.png
#ORIG_FILES += ../phy454/figures/continuumL13Fig13.png
#ORIG_FILES += ../phy454/figures/continuumProblemSet2Fig6mu1Gtmu2.png
#ORIG_FILES += ../phy454/figures/continuumProblemSet2Fig6mu2Gtmu1.png
#ORIG_FILES += ../phy454/figures/continuumProblemSet2Fig1r2.pdf
#ORIG_FILES += ../phy454/figures/continuumProblemSet2Fig1r2.pdf_tex
#ORIG_FILES += ../phy454/figures/continuumProblemSet2Fig2r2.pdf
#ORIG_FILES += ../phy454/figures/continuumProblemSet2Fig2r2.pdf_tex
#ORIG_FILES += ../phy454/figures/continuumProblemSet2Fig3.png
#ORIG_FILES += ../phy454/figures/continuumProblemSet2Fig4.png
#ORIG_FILES += ../phy454/figures/continuumProblemSet2Fig5.png
#ORIG_FILES += ../phy454/figures/inclinedFlowWithoutConstantHeightAssumptionFig1.png
#ORIG_FILES += ../phy454/figures/inclinedFlowWithoutConstantHeightAssumptionFig2.pdf
#ORIG_FILES += ../phy454/figures/inclinedFlowWithoutConstantHeightAssumptionFig2.pdf_tex
#ORIG_FILES += ../phy454/figures/inclinedFlowWithoutConstantHeightAssumptionFig3.pdf
#ORIG_FILES += ../phy454/figures/inclinedFlowWithoutConstantHeightAssumptionFig3.pdf_tex
#ORIG_FILES += ../gabook/gaQuickIntroFig1.pdf
#ORIG_FILES += ../gabook/gaQuickIntroFig1.pdf_tex
#ORIG_FILES += ../gabook/gaQuickIntroFig2.pdf
#ORIG_FILES += ../gabook/gaQuickIntroFig2.pdf_tex
#ORIG_FILES += ../phy454/figures/animatedTwoLayerFlowMu2GreaterThanMu1.avi
#ORIG_FILES += ../phy454/figures/animatedTwoLayerFlowMu1GreaterThanMu2.avi
#ORIG_FILES += ../phy454/figures/channelFlowWithStepPressureGradientTimeEvolution.wmv
#ORIG_FILES += ../strobe/StrobeMediaPlayback.swf

ORIG_FILES += ../phy454/figures/twoCylinderFig1.png
ORIG_FILES += ../phy454/figures/twoCylinderFig2.png
ORIG_FILES += ../phy454/figures/twoCylindersFig3.mp4
ORIG_FILES += ../phy454/figures/twoCylinderFig4.png
ORIG_FILES += ../phy454/figures/twoCylindersFig6.png
ORIG_FILES += ../phy454/figures/twoCylindersFig7.png
ORIG_FILES += ../phy454/figures/twoCylindersFig8.png
ORIG_FILES += ../phy454/figures/twoCylindersFig9.png
#ORIG_FILES += ../phy454/figures/coffeeCupWithBottomFig2.png
#ORIG_FILES += ../phy454/figures/coffeeCupWithBottomFig1.png

##       src/internal.o
#VIDEO += animatedTwoLayerFlowMu1GreaterThanMu2.mp4

LOCAL_FILES := $(notdir $(ORIG_FILES))

all :: $(LOCAL_FILES) $(PDFS) .gitignore
#all :: ftMaxVacuum.pdf
all :: peeters_macros.sty

.gitignore : GNUmakefile
	rm -f .gitignore
	echo $(ORIG_FILES) | tr ' ' '\n' | sed 's,.*/,notes/blogit/,' > $@

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
	perl ../make_pdflatex -file $<

#%.mp4 : %.avi
#	/cygdrive/c/Temp/ffmpeg/bin/ffmpeg -i $< -vcodec libx264 $@

%.mp4 : %.mov
	#/cygdrive/c/Temp/ffmpeg/bin/ffmpeg -i $< -vcodec copy -acodec copy $@
	/cygdrive/c/Temp/ffmpeg/bin/ffmpeg -i $< -vcodec libx264 $@

clean :: mostlyclean localclean

mostlyclean :: 
	rm -f *.ps *.dvi $(PDFS) *.aux *.log *.bbl *.blg *.brf *.toc *.stackdump *.bib

peeters_macros.sty : ../peeters_macros.tex $(THISDIR).sty
	cat ../peeters_macros.tex $(THISDIR).sty > $@

localclean ::
	rm -f $(LOCAL_FILES)
