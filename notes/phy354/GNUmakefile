include make.dep

ORIG_FILES += ../myrefs.bib
ORIG_FILES += ../abbrvurl.bst
ORIG_FILES += ../alphaurl.bst
ORIG_FILES += ../plainurl.bst
ORIG_FILES += ../unsrturl.bst

LOCAL_FILES := $(notdir $(ORIG_FILES))

all :: phy354.pdf

local : $(LOCAL_FILES) 

$(LOCAL_FILES) :
	cp $(filter %$@, $(ORIG_FILES)) $@

cronology.tex : ../METADATA
	../METADATA -phy354 > cronology.tex

phy354.pdf :: $(BOOKDEPENDENCIES) $(LOCAL_FILES)
	mkdir -p ./.revinfo/
	~/bin/mkRevInfo -book > ./.revinfo/lastCommitBook.tex
	../make_pdflatex main.tex
	mv main.pdf phy354.pdf

# FIXME: don't want pdf's in here!
clean ::
	rm -f *.ps *.dvi *.pdf *.aux *.log *.aux *.bbl *.blg *.idx *.lof *.log *.lot *.out *.toc $(LOCAL_FILES)
