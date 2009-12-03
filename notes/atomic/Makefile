files := $(shell ls *.tex)
pdfs := $(files:.tex=.pdf)

all : $(pdfs)

$(pdfs) : ../peeters_macros.tex

%.pdf : %.tex
	../make_pdflatex $<

clean ::
	rm -f *.ps *.dvi *.pdf *.aux *.log
