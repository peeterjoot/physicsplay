THISDIR := phy450

include ../make.vars

SOURCE_DIRS += figures
SOURCE_DIRS += solutions
SOURCE_DIRS += lectures
SOURCE_DIRS += problems

GENERATED_SOURCES += backmatter.tex

backmatter.tex : ../classicthesis.mine/backmatter.tex
	cp $< $@

include ../make.rules
