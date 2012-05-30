THISDIR := phy456

include ../make.vars

SOURCE_DIRS += approx
SOURCE_DIRS += figures
SOURCE_DIRS += handouts
SOURCE_DIRS += mathematica
SOURCE_DIRS += problems
SOURCE_DIRS += scattering
SOURCE_DIRS += spin

GENERATED_SOURCES := mathematica.tex 

include ../make.rules

peeters_macros.sty : ../peeters_macros.tex $(THISDIR).sty
	cat ../peeters_macros.tex $(THISDIR).sty > $@
