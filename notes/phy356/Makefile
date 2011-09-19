include make.dep

#ORIG_FILES += ../gabook/pendulumDouble.png
ORIG_FILES += ../myrefs.bib
ORIG_FILES += ../abbrvurl.bst
ORIG_FILES += ../alphaurl.bst
ORIG_FILES += ../plainurl.bst
ORIG_FILES += ../unsrturl.bst
ORIG_FILES += ../eliblog.cls 

LOCAL_FILES := $(notdir $(ORIG_FILES))

STANDALONE += desaiTypos.tex

PHY356 := $(filter-out $(STANDALONE), $(TEXFILES))

all :: phy356.pdf desaiTypos.pdf
#all :: t.pdf

local : $(LOCAL_FILES) 

$(LOCAL_FILES) :
	cp $(filter %$@, $(ORIG_FILES)) $@

cronology.tex : ../METADATA
	../METADATA -phy356 > cronology.tex

phy356.pdf :: $(PHY356) $(LOCAL_FILES)
	../make_pdflatex main.tex
	mv main.pdf phy356.pdf

desaiTypos.pdf :: desaiTypos.tex
	../make_pdflatex $<

#t.pdf :: t.tex
#	../make_pdflatex $<

#%.pdf : %.tex
#	../make_pdflatex $<

clean ::
	rm -f *.ps *.dvi *.pdf *.aux *.log *.aux *.bbl *.blg *.idx *.lof *.log *.lot *.out *.toc $(LOCAL_FILES)

phy356.pdf :: 
