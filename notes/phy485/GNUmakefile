THISDIR := phy485

include ../make.vars

SOURCE_DIRS += appendix
SOURCE_DIRS += solutions

GENERATED_SOURCES := mathematica.tex 

include ../make.rules

peeters_macros.sty : ../peeters_macros.tex
	cp $< $@

