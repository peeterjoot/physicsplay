all : gabook.pdf

# add here and as includes to gabook.tex:
gabook.pdf :: bivector.tex
gabook.pdf :: ga_wiki.tex
gabook.pdf :: ga_wiki_cramers.tex
gabook.pdf :: gabook.tex
gabook.pdf :: index.tex
gabook.pdf :: intro_ga.tex
gabook.pdf :: multivector_taylors.tex
gabook.pdf :: trivector.tex
gabook.pdf :: ga_wiki_torque.tex
gabook.pdf :: ga_wiki_unit_derivative.tex

%.pdf : %.tex
	../make_pdflatex $<

clean ::
	rm -f *.ps *.dvi *.pdf *.aux *.log *.aux *.bbl *.blg *.idx *.lof *.log *.lot *.out *.toc
