all : otherbook.pdf

TEXFILES += main.tex
TEXFILES += twobodies.tex
TEXFILES += scratchPlanewave.tex
TEXFILES += greens.tex
TEXFILES += stubEmFields.tex
TEXFILES += lorentzTxEmPotential.tex
TEXFILES += faradayLagrangian.tex
TEXFILES += voltageCurrentResistance.tex
TEXFILES += rindler.tex
TEXFILES += constantQ.tex
TEXFILES += euler.tex
TEXFILES += pfSch.tex
TEXFILES += m.tex
TEXFILES += box.tex
TEXFILES += lutQ0304.tex
TEXFILES += srLagrangianQ.tex
TEXFILES += reviewAlanGabook.tex
TEXFILES += reviewAlanGabookCh4.tex
TEXFILES += longWireQ.tex
TEXFILES += cronology.tex
TEXFILES +=

cronology.tex : ../gabook/METADATA
	../gabook/METADATA -otherbook > cronology.tex

otherbook.pdf :: $(TEXFILES)
	../make_pdflatex main.tex
	mv main.pdf otherbook.pdf

#%.pdf : %.tex
#	../make_pdflatex $<

clean ::
	rm -f *.ps *.dvi *.pdf *.aux *.log *.aux *.bbl *.blg *.idx *.lof *.log *.lot *.out *.toc
