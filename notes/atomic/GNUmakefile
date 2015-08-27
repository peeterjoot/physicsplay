TEXFILES := $(shell ls *.tex)
PDFS := $(TEXFILES:.tex=.pdf)

# logically symlinks, but MikTex doesn't like those:
ORIG_FILES += ../abbrvurl.bst
ORIG_FILES += ../alphaurl.bst
ORIG_FILES += ../myrefs.bib
ORIG_FILES += ../plainurl.bst
ORIG_FILES += ../unsrturl.bst
ORIG_FILES += ../eliblog.cls

include ../make.latexmk

LOCAL_FILES := $(notdir $(ORIG_FILES))

all :: $(PDFS) .gitignore

.gitignore : GNUmakefile
	rm -f .gitignore
	echo $(ORIG_FILES) $(COPIED_FILES) | tr ' ' '\n' | sed 's,.*/,notes/atomic/,' > $@

$(PDFS) : ../peeters_macros.tex $(LOCAL_FILES)

$(LOCAL_FILES) : $(ORIG_FILES)
	cp $(filter %$@, $(ORIG_FILES)) $@

%.pdf : %.tex
	$(LATEXMK) $<

clean ::
	rm -f *.ps *.dvi *.pdf *.aux *.log
