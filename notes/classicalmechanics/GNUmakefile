THISDIR := classicalmechanics
THISBOOK := $(THISDIR)

include ../latex/make.bookvars

FIGURES := ../../figures/$(THISBOOK)

#ONCEFLAGS := -justonce

SOURCE_DIRS += $(FIGURES)
SOURCE_DIRS += lectures
SOURCE_DIRS += galagrangian
SOURCE_DIRS += mine
SOURCE_DIRS += problems

GENERATED_SOURCES += mathematica.tex 
#GENERATED_SOURCES += backmatter.tex
GENERATED_SOURCES += cronology.tex

#ONCEFLAGS := -justonce

include ../latex/make.rules

#backmatter.tex : ../classicthesis_mine/backmatter.tex
#	cp $< $@
