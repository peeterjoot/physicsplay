TEXFILES := $(shell ls *.tex)
PDFS := $(TEXFILES:.tex=.pdf)

# logically symlinks, but MikTex doesn't like those:
ORIG_FILES += ../abbrvurl.bst
ORIG_FILES += ../alphaurl.bst
ORIG_FILES += ../myrefs.bib
ORIG_FILES += ../plainurl.bst
ORIG_FILES += ../unsrturl.bst
ORIG_FILES += ../eliblog.cls

LOCAL_FILES := $(notdir $(ORIG_FILES))

all :: $(PDFS)

$(PDFS) : ../peeters_macros.tex $(LOCAL_FILES)

$(LOCAL_FILES) : $(ORIG_FILES)
	cp $(filter %$@, $(ORIG_FILES)) $@

%.pdf : %.tex
	../make_pdflatex $<

clean ::
	rm -f *.ps *.dvi *.pdf *.aux *.log
