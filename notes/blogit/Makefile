files := $(shell ls *.tex)
pdfs := $(files:.tex=.pdf)

all : $(pdfs)

gaBasics.pdf : gaBasics.tex

# gaBasics.doc is currently my source for this document:
#
#gaBasics.tex : gaBasics.txt
#	./wordToTex < gaBasics.txt > gaBasics.tex

%.pdf : %.tex
	../make_pdflatex $<

clean ::
	rm -f *.ps *.dvi *.pdf *.aux *.log *.bbl *.blg
