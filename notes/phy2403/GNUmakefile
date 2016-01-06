THISDIR := phy2403

include ../make.vars
include ../make.rules

all :: $(notdir $(wildcard ../*.sty))
all :: Bibliography.bib

all :: qftProblemSet1.pdf
#all :: qftProblemSet2.pdf
all :: scalarFieldCreationOpCommutator.pdf
all :: scalarFieldHamiltonian.pdf

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

#Bibliography.bib : myrefs.bib
#	sed 's/@webpage/@manual/g' < $< > $@
#
## old style:
#myrefs.bib: ../myrefs.bib.in ../METADATA
#	cp ../myrefs.bib.in myrefs.bib
#	(cd .. ; ./METADATA -bib >> $(THISDIR)/myrefs.bib)



