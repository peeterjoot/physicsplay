THISDIR := gabookI

include ../make.bookvars

FIGURES := ../../figures/$(THISDIR)

SOURCE_DIRS += appendix
SOURCE_DIRS += basics
SOURCE_DIRS += calculus
SOURCE_DIRS += $(FIGURES)
SOURCE_DIRS += mathematica
SOURCE_DIRS += physics
SOURCE_DIRS += projection
SOURCE_DIRS += rotation

#SOURCE_DIRS += electrodynamics
#SOURCE_DIRS += emstress
#SOURCE_DIRS += fourier
#SOURCE_DIRS += lagrangian
#SOURCE_DIRS += lorentzforce
#SOURCE_DIRS += relativity
#SOURCE_DIRS += qm

ORIG_LISTING_DIRS += ../algebra
LOCAL_LISTING_FILES += levi.pl

GENERATED_SOURCES += mathematica.tex 
GENERATED_SOURCES += cronology.tex
GENERATED_SOURCES += backmatter.tex

#ONCEFLAGS := -justonce

GENERATED_PDFS += bigCollectionOfPartiallyIncorrectStokesTheoremMusings.pdf
GENERATED_PDFS += synopsisOfBigCollectionOfPartiallyIncorrectStokesTheoremMusings.pdf
GENERATED_PDFS += stokesTheoremGeometricAlgebra.pdf

include ../make.rules

listings/%.pl: %.pl
	mkdir -p $(@D)
	cp $< $@

backmatter.tex : ../classicthesis.mine/backmatter.tex
	cp $< $@

vpath %.png $(ORIG_FIGURE_DIRS)
vpath %.pl $(ORIG_LISTING_DIRS)

stokesTheoremGeometricAlgebra.pdf : calculus/stokesTheoremGeometricAlgebra.tex
