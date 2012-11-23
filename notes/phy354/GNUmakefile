THISDIR := phy354

include ../make.vars

SOURCE_DIRS += figures
SOURCE_DIRS += lectures
SOURCE_DIRS += galagrangian
SOURCE_DIRS += mine
SOURCE_DIRS += problems

GENERATED_SOURCES += mathematica.tex 
GENERATED_SOURCES += backmatter.tex

backmatter.tex : ../classicthesis.mine/backmatter.tex
	cp $< $@

include ../make.rules
