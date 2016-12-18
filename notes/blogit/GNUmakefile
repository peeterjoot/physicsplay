THISDIR := blogit

INKSCAPE := "/cygdrive/c/Program Files (x86)/Inkscape/inkscape.exe"
SDRAW := "/cygdrive/c/Program Files (x86)/LibreOffice 4/program/sdraw.exe"

RAWTEXFILES := $(shell ls *.tex)

CLEAN_TARGETS += $(PDFS) 
include ../latex/make.cleanvars

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
INCOMPLETE += groupAndPhase.tex
#INCOMPLETE += ps8mathematica.tex
INCOMPLETE += $(wildcard uwaves*Core.tex)
INCOMPLETE += uwavesDeck8ResonatorQfactor.tex
#INCOMPLETE += continuumAndOtherTransformers.tex

TEXFILES := $(filter-out $(INCOMPLETE), $(RAWTEXFILES)) 

PDFS := $(TEXFILES:.tex=.pdf)

LOCAL_FILES := $(notdir $(ORIG_FILES))

QPDF_DIR := $(wildcard /cygdrive/d/qpdf-*/bin $(HOME)/qpdf-*)
ifneq ($(QPDF_DIR),)
   QPDF := $(QPDF_DIR)/bin/qpdf.exe
endif

#EPS_FILES := $(wildcard *.eps)
#EPS_FILES := $(wildcard ../../figures/ece1229/*.eps)
EPS_FILES := $(wildcard ../../figures/ece1228-emt/*.eps)
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
all :: macros_cal.sty
all :: macros_lcal.sty
all :: macros_mathematica.sty
all :: $(LOCAL_FILES) $(PDFS) .gitignore
#all :: ftMaxVacuum.pdf
all :: multiPendulumSphericalMatrix.pdf

#druid.pdf : ../ece1228-electromagnetic-theory/druid.tex
gatutorial.pdf : ../ece1228-electromagnetic-theory/gaQuickTutorial.tex
uwavesDeck6LCmatching.pdf : ../ece1236-microwaves/uwavesDeck6LCmatchingCore.tex
continuumAndOtherTransformers.pdf : ../ece1236-microwaves/continuumAndOtherTransformersCore.tex
curlAndDivergenceVectorUniqueness.pdf : ../ece1228-electromagnetic-theory/gaPs1Problem5Attempt1.tex

multiPendulumSphericalMatrix.tex :: ../classicalmechanics/multiPendulumSphericalMatrix.tex
	cp $^ $@

.gitignore : GNUmakefile
	rm -f .gitignore
	echo $(ORIG_FILES) | tr ' ' '\n' | sedwrapper 's,.*/,notes/blogit/,' > $@

video: $(VIDEO)

$(PDFS) : $(LOCAL_FILES)

local : $(LOCAL_FILES)

$(LOCAL_FILES) : 
	cp $(filter %$@, $(ORIG_FILES)) $@

multiPendulumSphericalMatrix.pdf : ../classicalmechanics/mine/multiPendulumSphericalMatrix.tex

ensemblesForSpinOneHalf.pdf :: ../phy2403-qft/ensemblesForSpinOneHalf.tex

s1 : uwavesProblemSet1.pdf

uwavesProblemSet1.pdf : ../ece1236-microwaves/uwavesproblemSet1Problem1.tex \
../ece1236-microwaves/uwavesproblemSet1Problem2.tex \
../ece1236-microwaves/uwavesproblemSet1Problem3.tex \
../ece1236-microwaves/uwavesproblemSet1Problem4.tex \
../ece1236-microwaves/uwavesproblemSet1Problem5.tex

gaBasics.pdf : gaBasics.tex

# gaBasics.doc is currently my source for this document:
#
#gaBasics.tex : gaBasics.txt
#	./wordToTex < gaBasics.txt > gaBasics.tex

include ../latex/make.latexmk

%.pdf : %.tex
	mkdir -p ./.revinfo/
	mkRevInfo > ./.revinfo/lastCommit.tex
	mkRevInfo -date > ./.revinfo/gitCommitDate.tex
	mkRevInfo -commit > ./.revinfo/gitCommitString.tex
	mkRevInfo -repo > ./.revinfo/gitRepo.tex
	$(LATEXMK) $<

#%.mp4 : %.avi
#	/cygdrive/c/Temp/ffmpeg/bin/ffmpeg -i $< -vcodec libx264 $@

%.mp4 : %.mov
	#/cygdrive/c/Temp/ffmpeg/bin/ffmpeg -i $< -vcodec copy -acodec copy $@
	/cygdrive/c/Temp/ffmpeg/bin/ffmpeg -i $< -vcodec libx264 $@

clean :: mostlyclean localclean

mostlyclean :: 
	rm -f $(CLEAN_TARGETS)

peeters_layout.sty : ../latex/peeters_layout.sty
	cp $^ $@

peeters_figures.sty : ../latex/peeters_figures.sty
	cp $^ $@

ece1229.sty : ../ece1229-antenna/ece1229.sty
	cp $^ $@

hbFigure.sty : ../ece1254-multiphysics/hbFigure.sty
	cp $^ $@

peeters_layout_exercise.sty : ../latex/peeters_layout_exercise.sty
	cp $^ $@

peeters_macros.sty : ../latex/peeters_macros.sty
	cp $^ $@

peeters_braket.sty : ../latex/peeters_braket.sty
	cp $^ $@

macros_bm.sty : ../latex/macros_bm.sty
	cp $^ $@

macros_cal.sty : ../latex/macros_cal.sty
	cp $^ $@

macros_lcal.sty : ../latex/macros_lcal.sty
	cp $^ $@

macros_qed.sty : ../latex/macros_qed.sty
	cp $^ $@

matlab.sty : ../latex/matlab.sty
	cp $^ $@

macros_mathematica.sty : ../latex/macros_mathematica.sty
	cp $^ $@

Bibliography.bib : myrefs.bib
	sedwrapper 's/@webpage/@manual/g' < $< > $@

# old style:
myrefs.bib: ../latex/myrefs.bib.in ../METADATA
	cp ../latex/myrefs.bib.in myrefs.bib
	(cd .. ; ./METADATA -bib >> $(THISDIR)/myrefs.bib)

#ps8mathematica.tex : ../METADATA ../../mathematica/METADATA
#	(cd .. ; ./METADATA -mathematica -latex -phy2403 -filter phy2403/ps8/ ) > $@

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
