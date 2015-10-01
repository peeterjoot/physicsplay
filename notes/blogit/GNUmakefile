THISDIR := blogit

INKSCAPE := "/cygdrive/c/Program Files (x86)/Inkscape/inkscape.exe"
SDRAW := "/cygdrive/c/Program Files (x86)/LibreOffice 4/program/sdraw.exe"

RAWTEXFILES := $(shell ls *.tex)

CLEAN_TARGETS += $(PDFS) 
CLEAN_TARGETS += *.ilg *.ind *.idx *.ps *.dvi *.log *.aux *.bbl *.blg *.lof *.log *.lot *.out *.toc *.stackdump *.brf
CLEAN_TARGETS += *.synctex.gz

# buildable:
#INCOMPLETE += dotBlade.tex
INCOMPLETE += gaBasics.tex
INCOMPLETE += gaMintro.tex
#INCOMPLETE += maxwellsFromGA.tex
#INCOMPLETE += pipeFlowConstPressureGradient.tex
#INCOMPLETE += qmTwoExamReflection.tex
#INCOMPLETE += qmTwoR1.tex
INCOMPLETE += censor1l.tex
INCOMPLETE += censor1p.tex
INCOMPLETE += censor1pg.tex
INCOMPLETE += stokespost.tex
INCOMPLETE += gradQuantumProblemSet2Problem1.tex
INCOMPLETE += gradQuantumProblemSet2Problem2.tex
INCOMPLETE += gradQuantumProblemSet2Problem3.tex

TEXFILES := $(filter-out $(INCOMPLETE), $(RAWTEXFILES)) 

PDFS := $(TEXFILES:.tex=.pdf)

# for gaBasics:
#ORIG_FILES += ../phy454/figures/couetteFlowFig1.png
#ORIG_FILES += ../phy454/figures/couetteFlowFig2.png
#ORIG_FILES += ../phy454/figures/couetteFlowFig3.png
#ORIG_FILES += ../phy454/figures/couetteFlowFig4.png
#ORIG_FILES += ../phy454/figures/couetteFlowFig5.png
#ORIG_FILES += ../phy454/figures/couetteFlowFig6.mp4
#
#ORIG_FILES += ../phy454/figures/twoCylinderFig1.png
#ORIG_FILES += ../phy454/figures/twoCylinderFig2.png
#ORIG_FILES += ../phy454/figures/twoCylindersFig3.mp4
#ORIG_FILES += ../phy454/figures/twoCylinderFig4.png
#ORIG_FILES += ../phy454/figures/twoCylindersFig6.png
#ORIG_FILES += ../phy454/figures/twoCylindersFig7.png
#ORIG_FILES += ../phy454/figures/twoCylindersFig8.png
#ORIG_FILES += ../phy454/figures/twoCylindersFig9.png

##       src/internal.o
#VIDEO += animatedTwoLayerFlowMu1GreaterThanMu2.mp4

LOCAL_FILES := $(notdir $(ORIG_FILES))

QPDF_DIR := $(wildcard /cygdrive/d/qpdf-*/bin $(HOME)/qpdf-*)
ifneq ($(QPDF_DIR),)
   QPDF := $(QPDF_DIR)/bin/qpdf.exe
endif

#EPS_FILES := $(wildcard *.eps)
EPS_FILES := $(wildcard ../../figures/ece1229/*.eps)
PDFS_FROM_EPS := $(subst eps,pdf,$(EPS_FILES))

#ONCEFLAGS := -justonce
ONCEFLAGS := -nojustonce

all :: $(PDFS_FROM_EPS)
all :: Bibliography.bib
all :: peeters_macros.sty
all :: peeters_braket.sty
all :: peeters_figures.sty
all :: matlab.sty
all :: macros_qed.sty
all :: ece1229.sty
all :: peeters_layout.sty
all :: peeters_layout_exercise.sty
all :: macros_bm.sty
all :: macros_mathematica.sty
all :: $(LOCAL_FILES) $(PDFS) .gitignore
#all :: ftMaxVacuum.pdf

.gitignore : GNUmakefile
	rm -f .gitignore
	echo $(ORIG_FILES) | tr ' ' '\n' | sed 's,.*/,notes/blogit/,' > $@

video: $(VIDEO)

$(PDFS) : $(LOCAL_FILES)

local : $(LOCAL_FILES)

$(LOCAL_FILES) : 
	cp $(filter %$@, $(ORIG_FILES)) $@

energyMomentumWithMagneticSources.pdf : ../ece1229/energyMomentumWithMagneticSources.tex

gradQuantumProblemSet2.pdf : gradQuantumProblemSet2Problem1.tex
gradQuantumProblemSet2.pdf : gradQuantumProblemSet2Problem2.tex
gradQuantumProblemSet2.pdf : gradQuantumProblemSet2Problem3.tex

gaBasics.pdf : gaBasics.tex

# gaBasics.doc is currently my source for this document:
#
#gaBasics.tex : gaBasics.txt
#	./wordToTex < gaBasics.txt > gaBasics.tex

include ../make.latexmk

%.pdf : %.tex
	mkdir -p ./.revinfo/
	~/bin/mkRevInfo > ./.revinfo/lastCommit.tex
	~/bin/mkRevInfo -date > ./.revinfo/gitCommitDate.tex
	~/bin/mkRevInfo -commit > ./.revinfo/gitCommitString.tex
	~/bin/mkRevInfo -repo > ./.revinfo/gitRepo.tex
	$(LATEXMK) $<

#%.mp4 : %.avi
#	/cygdrive/c/Temp/ffmpeg/bin/ffmpeg -i $< -vcodec libx264 $@

%.mp4 : %.mov
	#/cygdrive/c/Temp/ffmpeg/bin/ffmpeg -i $< -vcodec copy -acodec copy $@
	/cygdrive/c/Temp/ffmpeg/bin/ffmpeg -i $< -vcodec libx264 $@

clean :: mostlyclean localclean

mostlyclean :: 
	rm -f $(CLEAN_TARGETS)

peeters_layout.sty : ../peeters_layout.sty
	cp $^ $@

peeters_figures.sty : ../peeters_figures.sty
	cp $^ $@

ece1229.sty : ../ece1229/ece1229.sty
	cp $^ $@

hbFigure.sty : ../ece1254/hbFigure.sty
	cp $^ $@

peeters_layout_exercise.sty : ../peeters_layout_exercise.sty
	cp $^ $@

peeters_macros.sty : ../peeters_macros.sty
	cp $^ $@

peeters_braket.sty : ../peeters_braket.sty
	cp $^ $@

macros_bm.sty : ../macros_bm.sty
	cp $^ $@

macros_qed.sty : ../macros_qed.sty
	cp $^ $@

matlab.sty : ../matlab.sty
	cp $^ $@

macros_mathematica.sty : ../macros_mathematica.sty
	cp $^ $@

Bibliography.bib : myrefs.bib
	sed 's/@webpage/@manual/g' < $< > $@

# old style:
myrefs.bib: ../myrefs.bib.in ../METADATA
	cp ../myrefs.bib.in myrefs.bib
	(cd .. ; ./METADATA -bib >> $(THISDIR)/myrefs.bib)

#ps3mathematica.tex : ../METADATA ../../mathematica/METADATA
#	(cd .. ; ./METADATA -mathematica -latex -ece1229 -filter ece1229/ps3/ ) > $@
opt/%.pdf : %.pdf
	mkdir -p opt
	$(QPDF) --linearize $< $@

%.pdf : %.eps
	epstopdf $^ --outfile=$@

# not ideal when legends include Mathematica traditional form output.  braces get lost in the mix, either
# with this conversion or the one from eps to pdf.
#%.eps : %.svg
#	$(INKSCAPE) $^ --export-eps=$@

# will this work (running from eps created directly in Mathematica?)
#%.png : %.eps
#	$(INKSCAPE) $^ --export-png=$@

%.eps : %.odg
	$(SDRAW) --headless --convert-to eps $^

%.png : %.odg
	$(SDRAW) --headless --convert-to png $^

# generates a black image (so does png from svg)
#%.png : %.pdf
#	$(INKSCAPE) $^ --export-png=$@

dist: presentation.pdf
	cp presentation.pdf pr/

localclean ::
	rm -f $(LOCAL_FILES)
