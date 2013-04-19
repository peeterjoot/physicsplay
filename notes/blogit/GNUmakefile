THISDIR := blogit

INKSCAPE := "/cygdrive/c/Program Files (x86)/Inkscape/inkscape.exe"
RAWTEXFILES := $(shell ls *.tex)

# buildable:
#INCOMPLETE += dotBlade.tex
#INCOMPLETE += gaBasics.tex
#INCOMPLETE += gaMintro.tex
#INCOMPLETE += maxwellsFromGA.tex
#INCOMPLETE += pipeFlowConstPressureGradient.tex
#INCOMPLETE += qmTwoExamReflection.tex
#INCOMPLETE += qmTwoR1.tex

TEXFILES := $(filter-out $(INCOMPLETE), $(RAWTEXFILES)) 

PDFS := $(TEXFILES:.tex=.pdf)

# for gaBasics:
ORIG_FILES += ../phy454/figures/couetteFlowFig1.png
ORIG_FILES += ../phy454/figures/couetteFlowFig2.png
ORIG_FILES += ../phy454/figures/couetteFlowFig3.png
ORIG_FILES += ../phy454/figures/couetteFlowFig4.png
ORIG_FILES += ../phy454/figures/couetteFlowFig5.png
ORIG_FILES += ../phy454/figures/couetteFlowFig6.mp4

ORIG_FILES += ../phy454/figures/twoCylinderFig1.png
ORIG_FILES += ../phy454/figures/twoCylinderFig2.png
ORIG_FILES += ../phy454/figures/twoCylindersFig3.mp4
ORIG_FILES += ../phy454/figures/twoCylinderFig4.png
ORIG_FILES += ../phy454/figures/twoCylindersFig6.png
ORIG_FILES += ../phy454/figures/twoCylindersFig7.png
ORIG_FILES += ../phy454/figures/twoCylindersFig8.png
ORIG_FILES += ../phy454/figures/twoCylindersFig9.png

##       src/internal.o
#VIDEO += animatedTwoLayerFlowMu1GreaterThanMu2.mp4

LOCAL_FILES := $(notdir $(ORIG_FILES))

QPDF_DIR := $(wildcard /cygdrive/d/qpdf-*/bin $(HOME)/qpdf-*)
ifneq ($(QPDF_DIR),)
   QPDF := $(QPDF_DIR)/bin/qpdf.exe
endif

all :: Bibliography.bib
all :: peeters_macros.sty
all :: peeters_layout.sty
all :: $(LOCAL_FILES) $(PDFS) .gitignore
#all :: ftMaxVacuum.pdf

huang93.pdf : ../phy452/basicStatMechProblemSet6Problem5.tex
#huang93.pdf : huang93Fig3sv.pdf
#huang93.pdf : huang93Fig4sv.pdf
#huang93.pdf : huang93Fig5sv.pdf
#huang93.pdf : huang93Fig2sv.pdf
#huang93.pdf : huang93Fig6sv.pdf

#all :: huang93Fig3sv.png
#all :: huang93Fig4sv.png
#all :: huang93Fig5sv.png
#all :: huang93Fig2sv.png
#all :: huang93Fig6sv.png

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
	~/bin/mkRevInfo -date > ./.revinfo/gitCommitDate.tex
	~/bin/mkRevInfo -commit > ./.revinfo/gitCommitString.tex
	~/bin/mkRevInfo -repo > ./.revinfo/gitRepo.tex
	perl ../make_pdflatex -nojustonce -file $<

#%.mp4 : %.avi
#	/cygdrive/c/Temp/ffmpeg/bin/ffmpeg -i $< -vcodec libx264 $@

%.mp4 : %.mov
	#/cygdrive/c/Temp/ffmpeg/bin/ffmpeg -i $< -vcodec copy -acodec copy $@
	/cygdrive/c/Temp/ffmpeg/bin/ffmpeg -i $< -vcodec libx264 $@

clean :: mostlyclean localclean

mostlyclean :: 
	rm -f *.ps *.dvi $(PDFS) *.aux *.log *.bbl *.blg *.brf *.toc *.stackdump *.bib

peeters_layout.sty : ../peeters_layout.sty
	cp $^ $@

peeters_macros.sty : ../peeters_macros.sty
	cp $^ $@

Bibliography.bib : myrefs.bib
	sed 's/@webpage/@manual/g' < $< > $@

# old style:
myrefs.bib: ../myrefs.bib.in ../METADATA
	cp ../myrefs.bib.in myrefs.bib
	../METADATA -bib >> myrefs.bib

opt/%.pdf : %.pdf
	mkdir -p opt
	$(QPDF) --linearize $< $@

#%.pdf : %.eps
#	epstopdf $^ --outfile=$@

# not ideal when legends include Mathematica traditional form output.  braces get lost in the mix, either
# with this conversion or the one from eps to pdf.
#%.eps : %.svg
#	$(INKSCAPE) $^ --export-eps=$@

# will this work (running from eps created directly in Mathematica?)
#%.png : %.eps
#	$(INKSCAPE) $^ --export-png=$@

# generates a black image (so does png from svg)
#%.png : %.pdf
#	$(INKSCAPE) $^ --export-png=$@

localclean ::
	rm -f $(LOCAL_FILES)
