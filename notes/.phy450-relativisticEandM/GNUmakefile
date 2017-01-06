THISDIR := phy450-relativisticEandM
THISBOOK := phy450

include ../latex/make.bookvars

#ONCEFLAGS := -justonce
THISBOOK_DEPS += poppitz.tex

FIGURES := ../../figures/$(THISBOOK)

SOURCE_DIRS += $(FIGURES)
SOURCE_DIRS += solutions
SOURCE_DIRS += lectures
SOURCE_DIRS += problems

GENERATED_SOURCES += mathematica.tex 
GENERATED_SOURCES += poppitz.tex

include ../latex/make.rules

backmatter.tex : ../classicthesis_mine/backmatter.tex
	cp $< $@

poppitz.tex : mkpref
	./mkpref > $@
