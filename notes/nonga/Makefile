include make.dep

ORIG_FILES += ../gabook/pendulumDouble.png
ORIG_FILES += ../myrefs.bib
ORIG_FILES += ../abbrvurl.bst
ORIG_FILES += ../alphaurl.bst
ORIG_FILES += ../plainurl.bst
ORIG_FILES += ../unsrturl.bst

LOCAL_FILES := $(notdir $(ORIG_FILES))

all : miscphysics.pdf

local : $(LOCAL_FILES) 

$(LOCAL_FILES) :
	cp $(filter %$@, $(ORIG_FILES)) $@

cronology.tex : ../gabook/METADATA
	../gabook/METADATA -miscbook > cronology.tex

miscphysics.pdf :: $(TEXFILES)
	../make_pdflatex main.tex
	mv main.pdf miscphysics.pdf

#%.pdf : %.tex
#	../make_pdflatex $<

clean ::
	rm -f *.ps *.dvi *.pdf *.aux *.log *.aux *.bbl *.blg *.idx *.lof *.log *.lot *.out *.toc
