THISDIR := classicalmechanics

include ../make.bookvars

FIGURES := ../../figures/$(THISDIR)

#ONCEFLAGS := -justonce

SOURCE_DIRS += $(FIGURES)
SOURCE_DIRS += lectures
SOURCE_DIRS += galagrangian
SOURCE_DIRS += mine
SOURCE_DIRS += problems

GENERATED_SOURCES += mathematica.tex 
GENERATED_SOURCES += backmatter.tex
GENERATED_SOURCES += cronology.tex

#ONCEFLAGS := -justonce

include ../make.rules

backmatter.tex : ../classicthesis.mine/backmatter.tex
	cp $< $@
