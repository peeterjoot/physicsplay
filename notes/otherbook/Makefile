all : otherbook.pdf

TEXFILES += gacsQ88.tex
TEXFILES += shear.tex
TEXFILES += twoNinetyRotations.tex
#TEXFILES += frequencyTx.tex
#TEXFILES += invarianceEnMom.tex
#TEXFILES += poincareTx.tex
#TEXFILES += stokesGradeTwo.tex
#TEXFILES += transverseField.tex
TEXFILES += interactionEnergy.tex
TEXFILES += lightQuantize.tex
TEXFILES += maxwellSepVars.tex
TEXFILES += maxwellVacuum_roughNotes.tex
TEXFILES += maxwellHomoFirstOrder.tex
TEXFILES += gaBasics.tex
TEXFILES += gradientAltCoord.tex
TEXFILES += epsilonMixed.tex
TEXFILES += dotBlade_rough.tex
TEXFILES += decodingMercedFlorez.tex
TEXFILES += qmbFirstTry.tex
TEXFILES += wedgeNormVsGaNorm.tex
TEXFILES += emTensor.tex
TEXFILES += matrixToOperator.tex
TEXFILES += schwartzchildMetric.tex
TEXFILES += tangentspace.tex
TEXFILES += waveguideRetardedAdvanced.tex
TEXFILES += maxwellLagRotate.tex
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
TEXFILES += bivectorSelectWrong.tex
TEXFILES += cronology.tex
TEXFILES += dotBlade.tex
TEXFILES += ellipticQ.tex
TEXFILES += gaMintro.tex
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
