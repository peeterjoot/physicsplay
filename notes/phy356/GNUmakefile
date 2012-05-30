THISDIR := phy356

include ../make.vars

SOURCE_DIRS += chapters
SOURCE_DIRS += figures
SOURCE_DIRS += FrontBackmatter

ORIG_FILES += ../myrefs.bib
ORIG_FILES += ../abbrvurl.bst
ORIG_FILES += ../alphaurl.bst
ORIG_FILES += ../plainurl.bst
ORIG_FILES += ../unsrturl.bst
ORIG_FILES += ../eliblog.cls

GENERATED_PDFS += desaiTypos.pdf

include ../make.rules

desaiTypos.pdf :: desaiTypos.tex
	mkdir -p ./.revinfo/
	~/bin/mkRevInfo > ./.revinfo/lastCommit.tex
	../make_pdflatex -file $<

peeters_macros.sty : ../peeters_macros.tex $(THISDIR).sty
	cat ../peeters_macros.tex $(THISDIR).sty > $@
