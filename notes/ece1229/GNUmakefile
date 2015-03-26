THISDIR := ece1229

include ../make.bookvars

#ONCEFLAGS := -justonce

SOURCE_DIRS += appendix
# FIXME:
# 1) including this incorrectly adds figures/*pdf to the ./.gitignore file
# 2) also not seeing this result in figure dependencies. touch figures/etalonFig1.pdf
FIGURES := ../../figures/$(THISDIR)
SOURCE_DIRS += $(FIGURES)

# also toggle redacted classicthesis-config.tex
# FIXME: changing this flag should be a dependency of matlab.tex 
#REDACTED := -redacted

GENERATED_SOURCES += matlab.tex 
GENERATED_SOURCES += mathematica.tex 
GENERATED_SOURCES += julia.tex 

#EPS_FILES := $(wildcard $(FIGURES)/report/*.eps)
#PDFS_FROM_EPS := $(subst eps,pdf,$(EPS_FILES))

THISBOOK_DEPS += $(PDFS_FROM_EPS)
THISBOOK_DEPS += macros_mathematica.sty

include ../make.rules

#epsconv : $(PDFS_FROM_EPS)

advancedantennaProblemSet1.pdf : advancedantennaProblemSet1Problem1.tex
advancedantennaProblemSet1.pdf : advancedantennaProblemSet1Problem2.tex
advancedantennaProblemSet1.pdf : advancedantennaProblemSet1Problem3.tex
advancedantennaProblemSet1.pdf : advancedantennaProblemSet1Problem4.tex
advancedantennaProblemSet1.pdf : advancedantennaProblemSet1Problem5.tex
advancedantennaProblemSet1.pdf : advancedantennaProblemSet1Problem6.tex

#ps3mathematica.tex : ../METADATA ../../mathematica/METADATA
#	(cd .. ; ./METADATA -mathematica -latex -ece1229 -filter ece1229/ps3/ ) > $@
