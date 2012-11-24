THISDIR := phy356

include ../make.vars

SOURCE_DIRS += chapters
SOURCE_DIRS += figures

GENERATED_PDFS += desaiTypos.pdf
GENERATED_SOURCES += backmatter.tex

include ../make.rules

backmatter.tex : ../classicthesis.mine/backmatter.tex
	cp $< $@
