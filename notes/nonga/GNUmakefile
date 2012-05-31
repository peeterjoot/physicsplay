THISDIR := miscphysics

include ../make.vars

SOURCE_DIRS += figures
SOURCE_DIRS += solutions
SOURCE_DIRS += lectures
SOURCE_DIRS += problems

ORIG_FILES += ../gabook/pendulumDouble.png

GENERATED_SOURCES := cronology.tex

include ../make.rules

peeters_macros.sty : ../peeters_macros.tex $(THISDIR).sty
	cat ../peeters_macros.tex $(THISDIR).sty > $@
