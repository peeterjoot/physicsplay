all : nonga.pdf

TEXFILES += main.tex
#TEXFILES += new_commands.tex
TEXFILES += accFourVector.tex
TEXFILES += accFourVector.tex
TEXFILES += pauliFourVectorV.tex
TEXFILES += pauliQmRelativityIntro.tex
TEXFILES += velocityAddition.tex
TEXFILES += taylors.tex
TEXFILES += maxwell.tex
TEXFILES += goldsteinCh12.tex
TEXFILES += tangentspace.tex
TEXFILES += schwartzchildMetric.tex
TEXFILES += distributions.tex
TEXFILES += fletcher.tex
TEXFILES += fletcher.tex
TEXFILES += starDistance.tex
TEXFILES += debroglie.tex
TEXFILES += binomial.tex
TEXFILES += dotLinearity.tex
TEXFILES += byronFullerCalcVar.tex
TEXFILES += wavevariation.tex
TEXFILES += twobodies.tex
TEXFILES += bohm11.tex
TEXFILES += bohmCh10.tex
TEXFILES += bohmCh9.tex
TEXFILES += commutatorHerm.tex
TEXFILES += deltaOrthoSeries.tex
TEXFILES += ehrenfest.tex
TEXFILES += gaussian.tex
TEXFILES += harmonicOsc.tex
TEXFILES += kleinGordon.tex
TEXFILES += qmBarrier.tex
TEXFILES += qmSusskind.tex
TEXFILES += qmbFirstTry.tex
TEXFILES += qmdCh2quiz.tex
TEXFILES += wavepacket.tex
TEXFILES += faradayLagrangian.tex
TEXFILES += fvec.tex
TEXFILES += gacsQ88.tex
TEXFILES += greens.tex
TEXFILES += matrixToOperator.tex
TEXFILES += mpInverseSvdRoughNotes.tex
TEXFILES += pe.tex
TEXFILES += pythagoras.tex
TEXFILES += rapidity.tex
TEXFILES += sch.tex
TEXFILES += shear.tex
TEXFILES += twoNinetyRotations.tex
TEXFILES += waveLagrangian.tex
TEXFILES += wedgeNormVsGaNorm.tex
TEXFILES += voltageCurrentResistance.tex
TEXFILES += emTensor.tex
TEXFILES += lorentzMetricTensor.tex
TEXFILES += euler.tex
TEXFILES += constantQ.tex
#TEXFILES += lutQ0304.tex
TEXFILES += rindler.tex
TEXFILES += srLagrangianQ.tex
TEXFILES += m.tex
TEXFILES += scratchPlanewave.tex
TEXFILES += stubEmFields.tex
TEXFILES += box.tex
TEXFILES += longWireQ.tex
TEXFILES += lorentzTxEmPotential.tex
TEXFILES += pfSch.tex
TEXFILES += reviewAlanGabook.tex
TEXFILES += reviewAlanGabookCh4.tex
TEXFILES += lutQ0304.tex
TEXFILES += cross.tex
TEXFILES += cronology.tex
TEXFILES += crossOld.tex
TEXFILES +=

cronology.tex : ../gabook/METADATA
	../gabook/METADATA -miscbook > cronology.tex

nonga.pdf :: $(TEXFILES)
	../make_pdflatex main.tex
	mv main.pdf nonga.pdf

#%.pdf : %.tex
#	../make_pdflatex $<

clean ::
	rm -f *.ps *.dvi *.pdf *.aux *.log *.aux *.bbl *.blg *.idx *.lof *.log *.lot *.out *.toc
