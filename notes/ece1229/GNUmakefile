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

#all :: advancedantennaProblemSet4.pdf

#epsconv : $(PDFS_FROM_EPS)

advancedantennaProblemSet1.pdf : advancedantennaProblemSet1Problem1.tex
advancedantennaProblemSet1.pdf : advancedantennaProblemSet1Problem2.tex
advancedantennaProblemSet1.pdf : advancedantennaProblemSet1Problem3.tex
advancedantennaProblemSet1.pdf : advancedantennaProblemSet1Problem4.tex
advancedantennaProblemSet1.pdf : advancedantennaProblemSet1Problem5.tex
advancedantennaProblemSet1.pdf : advancedantennaProblemSet1Problem6.tex

advancedantennaProblemSet4.pdf : advancedantennaProblemSet4Problem1.tex
advancedantennaProblemSet4.pdf : advancedantennaProblemSet4Problem2.tex
advancedantennaProblemSet4.pdf : advancedantennaProblemSet4Problem3.tex
advancedantennaProblemSet4.pdf : advancedantennaProblemSet4Problem4.tex
advancedantennaProblemSet4.pdf : ps4mathematica.tex
advancedantennaProblemSet4.pdf : ps4matlab.tex
advancedantennaProblemSet4.pdf : ps4julia.tex

advancedantennaProblemSet5.pdf : ps5matlab.tex
advancedantennaProblemSet5.pdf : ps5mathematica.tex
#INCOMPLETE += ps5mathematica.tex
#INCOMPLETE += ps5matlab.tex
#INCOMPLETE += advancedantennaProblemSet5Problem1.tex
#INCOMPLETE += advancedantennaProblemSet5Problem2.tex

ps5matlab.tex : ../METADATA ../../matlab/METADATA
	(cd .. ; ./METADATA -matlab -latex -ece1229 -filter ece1229/ps5/ ) > $@

ps5mathematica.tex : ../METADATA ../../mathematica/METADATA
	(cd .. ; ./METADATA -mathematica -latex -ece1229 -filter ece1229/ps5/ ) > $@

ps4mathematica.tex : ../METADATA ../../mathematica/METADATA
	(cd .. ; ./METADATA -mathematica -latex -ece1229 -filter ece1229/ps4/ ) > $@

ps4matlab.tex : ../METADATA ../../matlab/METADATA
	(cd .. ; ./METADATA -matlab -latex -ece1229 -filter ece1229/ps4/ ) > $@

ps4julia.tex : ../METADATA ../../julia/METADATA
	(cd .. ; ./METADATA -julia -latex -ece1229 -filter ece1229/ps4/ ) > $@

ps3mathematica.tex : ../METADATA ../../mathematica/METADATA
	(cd .. ; ./METADATA -mathematica -latex -ece1229 -filter ece1229/ps3/ ) > $@
