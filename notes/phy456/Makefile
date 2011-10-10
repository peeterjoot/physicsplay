include make.dep

ORIG_FILES += ../myrefs.bib
ORIG_FILES += ../abbrvurl.bst
ORIG_FILES += ../alphaurl.bst
ORIG_FILES += ../plainurl.bst
ORIG_FILES += ../unsrturl.bst
ORIG_FILES += ../eliblog.cls 

LOCAL_FILES := $(notdir $(ORIG_FILES))

PHY456 := $(filter-out $(STANDALONE), $(TEXFILES))

PDFS := phy456.pdf

all :: $(PDFS)

local : $(LOCAL_FILES) 

$(LOCAL_FILES) :
	cp $(filter %$@, $(ORIG_FILES)) $@

cronology.tex : ../METADATA
	../METADATA -phy456 > cronology.tex

phy456.pdf :: $(PHY456) $(LOCAL_FILES)
	../make_pdflatex main.tex
	mv main.pdf phy456.pdf

clean ::
	rm -f *.ps *.dvi $(PDFS) *.aux *.log *.aux *.bbl *.blg *.idx *.lof *.log *.lot *.out *.toc $(LOCAL_FILES)
