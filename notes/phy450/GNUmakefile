THISDIR := phy450

include ../make.vars

SOURCE_DIRS += figures
SOURCE_DIRS += solutions
SOURCE_DIRS += lectures
SOURCE_DIRS += problems

GENERATED_SOURCES += backmatter.tex
GENERATED_SOURCES += mathematica.tex 

include ../make.rules

backmatter.tex : ../classicthesis.mine/backmatter.tex
	cp $< $@
