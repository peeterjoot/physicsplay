all : miscphysics.pdf

include make.dep

cronology.tex : ../gabook/METADATA
	../gabook/METADATA -miscbook > cronology.tex

miscphysics.pdf :: $(TEXFILES)
	../make_pdflatex main.tex
	mv main.pdf miscphysics.pdf

#%.pdf : %.tex
#	../make_pdflatex $<

clean ::
	rm -f *.ps *.dvi *.pdf *.aux *.log *.aux *.bbl *.blg *.idx *.lof *.log *.lot *.out *.toc
