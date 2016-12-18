THISDIR := phy2403-qft
THISBOOK := phy2403

include ../latex/make.vars
include ../latex/make.rules

all :: $(notdir $(wildcard ../*.sty))
all :: Bibliography.bib

SOURCES += noetherCurrentScalarField.tex
SOURCES += scalarFieldCreationOpCommutator.tex
SOURCES += scalarFieldHamiltonian.tex
SOURCES += qftProblemSet1.tex
#SOURCES += qftProblemSet2.tex

all :: $(subst tex,pdf,$(SOURCES))

qftProblemSet1.pdf : qftProblemSet1Problem1.tex
qftProblemSet1.pdf : qftProblemSet1Problem2.tex
qftProblemSet1.pdf : qftProblemSet1Problem3.tex
qftProblemSet1.pdf : qftProblemSet1Problem4.tex
qftProblemSet1.pdf : qftProblemSet1Problem5.tex
qftProblemSet1.pdf : qftProblemSet1Problem6.tex

#qftProblemSet2.pdf : qftProblemSet2Problem1.tex
#qftProblemSet2.pdf : qftProblemSet2Problem2.tex
#qftProblemSet2.pdf : qftProblemSet2Problem3.tex
#qftProblemSet2.pdf : qftProblemSet2Problem4.tex
#qftProblemSet2.pdf : qftProblemSet2Problem5.tex

