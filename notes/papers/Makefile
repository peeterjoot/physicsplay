RAWTEXFILES := $(shell ls *.tex)

TEXFILES := $(filter-out $(INCOMPLETE), $(RAWTEXFILES)) 

PDFS := $(TEXFILES:.tex=.pdf)

# logically symlinks, but MikTex doesn't like those:
ORIG_FILES += ../abbrvurl.bst
ORIG_FILES += ../alphaurl.bst
ORIG_FILES += ../eliblog.cls 
ORIG_FILES += ../eliblogwidescreen.cls 
ORIG_FILES += ../myrefs.bib 
ORIG_FILES += ../plainurl.bst
ORIG_FILES += ../unsrturl.bst

LOCAL_FILES := $(notdir $(ORIG_FILES))

all :: $(LOCAL_FILES) $(PDFS)

$(PDFS) : $(LOCAL_FILES)

local : $(LOCAL_FILES)

$(LOCAL_FILES) : 
	cp $(filter %$@, $(ORIG_FILES)) $@

%.pdf : %.tex
	perl ../make_pdflatex $<

clean :: mostlyclean localclean

mostlyclean :: 
	rm -f *.ps *.dvi *.pdf *.aux *.log *.bbl *.blg *.brf *.toc *.stackdump *.bib

localclean ::
	rm -f $(LOCAL_FILES)
