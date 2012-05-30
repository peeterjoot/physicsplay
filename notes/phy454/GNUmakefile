THISDIR := phy454

include ../make.varsPre

SOURCE_DIRS += appendix
SOURCE_DIRS += figures
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
SOURCE_DIRS += FrontBackmatter
SOURCE_DIRS += intro
SOURCE_DIRS += solutions

GENERATED_SOURCES := mathematica.tex 

include ../make.varsPost

include ../make.rules

peeters_macros.sty : ../peeters_macros.tex
	cp $< $@

