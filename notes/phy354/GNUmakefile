THISDIR := phy354

include ../make.vars

SOURCE_DIRS += figures
SOURCE_DIRS += lectures
SOURCE_DIRS += mine
SOURCE_DIRS += problems

GENERATED_SOURCES := mathematica.tex 

include ../make.rules

peeters_macros.sty : ../peeters_macros.tex
	cp $< $@

