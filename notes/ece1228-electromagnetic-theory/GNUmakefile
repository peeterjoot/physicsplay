THISDIR := ece1228-electromagnetic-theory
THISBOOK := ece1228

include ../make.bookvars

#ONCEFLAGS := -justonce

SOURCE_DIRS += appendix
FIGURES := ../../figures/$(THISBOOK)
SOURCE_DIRS += $(FIGURES)

# also toggle redacted classicthesis-config.tex
# FIXME: changing this flag should be a dependency of matlab.tex 
#REDACTED := -redacted

#GENERATED_SOURCES += matlab.tex 
GENERATED_SOURCES += mathematica.tex 
#GENERATED_SOURCES += julia.tex 

EPS_FILES := $(wildcard $(FIGURES)/*.eps)
PDFS_FROM_EPS := $(subst eps,pdf,$(EPS_FILES))

THISBOOK_DEPS += $(PDFS_FROM_EPS)
#THISBOOK_DEPS += macros_mathematica.sty

include ../make.rules

#all:: emtLecture10.pdf
all :: emtLecture10PartII.pdf

#l2 : emtLecture2.pdf
#l3 : emtLecture3.pdf
#l4 : emtLecture4.pdf
#l5 : emtLecture5.pdf
#l6 : emtLecture6.pdf
#l7 : emtLecture7.pdf
#l8 : emtLecture8.pdf
l9 : emtLecture9.pdf
#l10 : emtLecture10.pdf
l10b : emtLecture10PartII.pdf
#p1 : emtProblemSet1.pdf
#p2 : emtProblemSet2.pdf
#p3 : emtProblemSet3.pdf
#p4 : emtProblemSet4.pdf
#p5 : emtProblemSet5.pdf
#p6 : emtProblemSet6.pdf
#p7 : emtProblemSet7.pdf
#p8 : emtProblemSet8.pdf
p9 : emtProblemSet9.pdf
#pd : dipoleMoment.pdf
#pv : dipolePotential.pdf

emtProblemSet1.pdf : emtProblemSet1Problem1.tex
emtProblemSet1.pdf : emtProblemSet1Problem2.tex
emtProblemSet1.pdf : emtProblemSet1Problem3.tex
emtProblemSet1.pdf : emtProblemSet1Problem4.tex
emtProblemSet1.pdf : emtProblemSet1Problem5.tex
emtProblemSet1.pdf : emtProblemSet1Problem6.tex
#emtProblemSet1.pdf : emtProblemSet1Appendix.tex
#emtProblemSet1.pdf : gaQuickTutorial.tex
#emtProblemSet1.pdf : gaPs1Problem5Attempt1.tex

emtProblemSet2.pdf : emtProblemSet2Problem1.tex
emtProblemSet2.pdf : emtProblemSet2Problem2.tex
emtProblemSet2.pdf : emtProblemSet2Problem3.tex
emtProblemSet2.pdf : emtProblemSet2Problem4.tex
emtProblemSet2.pdf : emtProblemSet2Problem5.tex

emtProblemSet3.pdf : emtProblemSet3Problem1.tex
emtProblemSet3.pdf : emtProblemSet3Problem2.tex
emtProblemSet3.pdf : emtProblemSet3Problem3.tex
emtProblemSet3.pdf : emtProblemSet3Problem4.tex
#emtProblemSet3.pdf : emtProblemSet3Appendix.tex

emtProblemSet4.pdf : emtProblemSet4Problem1.tex
emtProblemSet4.pdf : emtProblemSet4Problem2.tex
emtProblemSet4.pdf : emtProblemSet4Problem3.tex
emtProblemSet4.pdf : emtProblemSet4Problem4.tex

emtProblemSet5.pdf : emtProblemSet5Problem1.tex
emtProblemSet5.pdf : emtProblemSet5Problem2.tex
emtProblemSet5.pdf : emtProblemSet5Problem3.tex
emtProblemSet5.pdf : ps5mathematica.tex

emtProblemSet6.pdf : emtProblemSet6Problem1.tex
emtProblemSet6.pdf : emtProblemSet6Problem2.tex
emtProblemSet6.pdf : emtProblemSet6Problem3.tex

emtProblemSet7.pdf : emtProblemSet7Problem1.tex
emtProblemSet7.pdf : emtProblemSet7Problem2.tex
emtProblemSet7.pdf : emtProblemSet7Problem3.tex

emtProblemSet8.pdf : emtProblemSet8Problem1.tex
emtProblemSet8.pdf : emtProblemSet8Problem2.tex
emtProblemSet8.pdf : emtProblemSet8Problem3.tex

emtProblemSet9.pdf : emtProblemSet9Problem1.tex
emtProblemSet9.pdf : emtProblemSet9Problem2.tex
emtProblemSet9.pdf : emtProblemSet9Problem3.tex

julia.tex : ../../julia/METADATA
mathematica.tex : ../../mathematica/METADATA
matlab.tex : ../../matlab/METADATA

ps5mathematica.tex : ../METADATA ../../mathematica/METADATA
	(cd .. ; ./METADATA -mathematica -latex -ece1228 -filter ece1228-emt/ps5/ ) > $@
