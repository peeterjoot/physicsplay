include make.dep

ORIG_FILES += ../myrefs.bib
ORIG_FILES += ../abbrvurl.bst
ORIG_FILES += ../alphaurl.bst
ORIG_FILES += ../plainurl.bst
ORIG_FILES += ../unsrturl.bst
ORIG_FILES += ../eliblog.cls 
ORIG_FILES += ../strobe/StrobeMediaPlayback.swf

URLPATH := http://peeterjoot.hostei.com/phy454/

LOCAL_FILES := $(notdir $(ORIG_FILES))

PHY454 := $(filter-out $(STANDALONE), $(BOOKDEPENDENCIES))

GENERATED_PDFS := phy454.pdf

all :: $(GENERATED_PDFS)

local : $(LOCAL_FILES) 

$(LOCAL_FILES) :
	cp $(filter %$@, $(ORIG_FILES)) $@

cronology.tex : ../METADATA
	../METADATA -phy454 > cronology.tex

mathematica.tex : ../METADATA
	../METADATA -mathematica -latex -phy454 > mathematica.tex

phy454.pdf :: $(PHY454) $(LOCAL_FILES) mathematica.tex
	mkdir -p ./.revinfo/
	~/bin/mkRevInfo -book > ./.revinfo/lastCommitBook.tex
	../make_pdflatex main.tex
	mv main.pdf phy454.pdf

# backed up .mp4's (and .avi's) to:
animatedTwoLayerFlowMu2GreaterThanMu1Try3.mp4 :
	wget $(URLPATH)animatedTwoLayerFlowMu2GreaterThanMu1Try3.mp4

animatedTwoLayerFlowMu1GreaterThanMu2Try3.mp4 :
	wget $(URLPATH)animatedTwoLayerFlowMu1GreaterThanMu2Try3.mp4

channelFlowWithStepPressureGradientEarlyTimeEvolution.mp4 : 
	wget $(URLPATH)channelFlowWithStepPressureGradientEarlyTimeEvolution.mp4

channelFlowWithStepPressureGradientTimeEvolution.mp4 : 
	wget $(URLPATH)channelFlowWithStepPressureGradientTimeEvolution.mp4

clean ::
	rm -f *.ps *.dvi $(GENERATED_PDFS) *.aux *.log *.aux *.bbl *.blg *.idx *.lof *.log *.lot *.out *.toc $(LOCAL_FILES)
