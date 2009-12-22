TEXFILES := $(shell ls *.tex)
PDFS := $(TEXFILES:.tex=.pdf)

# logically symlinks, but MikTex doesn't like those:
SYMLINKS += abbrvurl.bst
SYMLINKS += alphaurl.bst
SYMLINKS += eliblog.cls 
SYMLINKS += myrefs.bib 
SYMLINKS += plainurl.bst
SYMLINKS += unsrturl.bst

all :: $(SYMLINKS) $(PDFS)

$(PDFS) : eliblog.cls myrefs.bib

% : ../%
	cp $^ $@

gaBasics.pdf : gaBasics.tex

# gaBasics.doc is currently my source for this document:
#
#gaBasics.tex : gaBasics.txt
#	./wordToTex < gaBasics.txt > gaBasics.tex

%.pdf : %.tex
	../make_pdflatex $<

clean ::
	rm -f *.ps *.dvi *.pdf *.aux *.log *.bbl *.blg
