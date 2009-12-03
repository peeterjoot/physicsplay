all : otherbook.pdf

include make.dep

cronology.tex : ../gabook/METADATA
	../gabook/METADATA -otherbook > cronology.tex

otherbook.pdf :: $(TEXFILES)
	../make_pdflatex main.tex
	mv main.pdf otherbook.pdf

#%.pdf : %.tex
#	../make_pdflatex $<

clean ::
	rm -f *.ps *.dvi *.pdf *.aux *.log *.aux *.bbl *.blg *.idx *.lof *.log *.lot *.out *.toc
