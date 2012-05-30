THISDIR := phy450

include ../make.vars

SOURCE_DIRS += figures
SOURCE_DIRS += FrontBackmatter
SOURCE_DIRS += solutions
SOURCE_DIRS += lectures
SOURCE_DIRS += problems

include ../make.rules

peeters_macros.sty : ../peeters_macros.tex $(THISDIR).sty
	cat ../peeters_macros.tex $(THISDIR).sty > $@
