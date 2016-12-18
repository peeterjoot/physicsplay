THISDIR := phy454-continuumechanics
THISBOOK := phy454

include ../latex/make.bookvars

FIGURES := ../../figures/$(THISBOOK)

SOURCE_DIRS += appendix
SOURCE_DIRS += figures
SOURCE_DIRS += $(FIGURES)
SOURCE_DIRS += elastic/displacements
SOURCE_DIRS += elastic/strain
SOURCE_DIRS += elastic/stress
SOURCE_DIRS += fluids
SOURCE_DIRS += fluids/bernoulli
SOURCE_DIRS += fluids/boundaryLayers
SOURCE_DIRS += fluids/hydrostatics
SOURCE_DIRS += fluids/navierStokes
SOURCE_DIRS += fluids/nondimensionalisation
SOURCE_DIRS += fluids/singularPertubation
SOURCE_DIRS += fluids/surfaces
SOURCE_DIRS += fluids/surfaceTension
SOURCE_DIRS += fluids/thermal
SOURCE_DIRS += intro
SOURCE_DIRS += solutions

GENERATED_SOURCES += mathematica.tex 
GENERATED_SOURCES += backmatter.tex

include ../latex/make.rules

backmatter.tex : ../phy487-qmsolids/backmatter.tex
	cp $< $@
