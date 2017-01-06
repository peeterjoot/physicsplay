THISDIR := phy456-qmII
THISBOOK := phy456

include ../latex/make.bookvars

FIGURES := ../../figures/$(THISBOOK)

#ONCEFLAGS := -justonce

SOURCE_DIRS += approx
SOURCE_DIRS += handouts
SOURCE_DIRS += mathematica
SOURCE_DIRS += problems
SOURCE_DIRS += scattering
SOURCE_DIRS += spin
SOURCE_DIRS += $(FIGURES)

GENERATED_SOURCES += mathematica.tex 
#GENERATED_SOURCES += backmatter.tex

include ../latex/make.rules

#backmatter.tex : ../classicthesis_mine/backmatter.tex
#	cp $< $@
