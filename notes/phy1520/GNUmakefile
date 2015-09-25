THISDIR := phy1520

include ../make.bookvars

#ONCEFLAGS := -justonce

SOURCE_DIRS += appendix
FIGURES := ../../figures/$(THISDIR)
SOURCE_DIRS += $(FIGURES)

# also toggle redacted classicthesis-config.tex
# FIXME: changing this flag should be a dependency of matlab.tex 
#REDACTED := -redacted

#GENERATED_SOURCES += matlab.tex 
#GENERATED_SOURCES += mathematica.tex 
GENERATED_SOURCES += julia.tex 

EPS_FILES := $(wildcard $(FIGURES)/*.eps)
PDFS_FROM_EPS := $(subst eps,pdf,$(EPS_FILES))

THISBOOK_DEPS += $(PDFS_FROM_EPS)
#THISBOOK_DEPS += macros_mathematica.sty

include ../make.rules

#problemSets : gradQuantumProblemSet1.pdf gradQuantumProblemSet2.pdf

#gradQuantumProblemSet5.pdf : gradQuantumProblemSet5Problem1.tex
#gradQuantumProblemSet5.pdf : gradQuantumProblemSet5Problem2.tex
#gradQuantumProblemSet5.pdf : ps5matlab.tex
#gradQuantumProblemSet5.pdf : ps5mathematica.tex
#gradQuantumProblemSet5.pdf : matlab.sty

#ps5matlab.tex : ../METADATA ../../matlab/METADATA
#	(cd .. ; ./METADATA -matlab -latex -phy1520 -filter phy1520/ps5/ ) > $@
#
#ps5mathematica.tex : ../METADATA ../../mathematica/METADATA
#	(cd .. ; ./METADATA -mathematica -latex -phy1520 -filter phy1520/ps5/ ) > $@
