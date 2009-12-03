all : gabook.pdf

include make.dep

cronology.tex : METADATA
	./METADATA -gabook > cronology.tex

gabook.pdf :: $(TEXFILES)
	../make_pdflatex main.tex
	mv main.pdf gabook.pdf

#%.pdf : %.tex
#	../make_pdflatex $<

clean ::
	rm -f *.ps *.dvi *.pdf *.aux *.log *.aux *.bbl *.blg *.idx *.lof *.log *.lot *.out *.toc
