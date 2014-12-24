THISDIR := phy450

include ../make.bookvars

#ONCEFLAGS := -justonce

FIGURES := ../../figures/$(THISDIR)

SOURCE_DIRS += $(FIGURES)
SOURCE_DIRS += solutions
SOURCE_DIRS += lectures
SOURCE_DIRS += problems

GENERATED_SOURCES += backmatter.tex
GENERATED_SOURCES += mathematica.tex 

include ../make.rules

backmatter.tex : ../classicthesis.mine/backmatter.tex
	cp $< $@

poppitz.tex : mkpref
	./mkpref > $@
