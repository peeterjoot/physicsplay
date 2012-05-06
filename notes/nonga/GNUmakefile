include make.dep

ORIG_FILES += ../gabook/pendulumDouble.png
ORIG_FILES += ../myrefs.bib
ORIG_FILES += ../abbrvurl.bst
ORIG_FILES += ../alphaurl.bst
ORIG_FILES += ../plainurl.bst
ORIG_FILES += ../unsrturl.bst

LOCAL_FILES := $(notdir $(ORIG_FILES))

all : miscphysics.pdf .gitignore

local : $(LOCAL_FILES) 

.gitignore : GNUmakefile
	rm -f .gitignore
	echo $(ORIG_FILES) | tr ' ' '\n' | sed 's,.*/,notes/nonga/,' > $@

$(LOCAL_FILES) :
	cp $(filter %$@, $(ORIG_FILES)) $@

cronology.tex : ../METADATA
	../METADATA -miscbook > cronology.tex

miscphysics.pdf :: $(BOOKDEPENDENCIES) $(LOCAL_FILES)
	mkdir -p ./.revinfo/
	~/bin/mkRevInfo -book > ./.revinfo/lastCommitBook.tex
	../make_pdflatex main.tex
	mv main.pdf miscphysics.pdf

#%.pdf : %.tex
#	mkdir -p ./.revinfo/
#	~/bin/mkRevInfo > ./.revinfo/lastCommit.tex
#	../make_pdflatex $<

clean ::
	rm -f *.ps *.dvi *.pdf *.aux *.log *.aux *.bbl *.blg *.idx *.lof *.log *.lot *.out *.toc $(LOCAL_FILES)
