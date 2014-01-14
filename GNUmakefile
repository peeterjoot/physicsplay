SUBMAKES := $(wildcard notes/*/GNUmakefile)
SUBDIRS := $(subst /GNUmakefile,,$(SUBMAKES))
IGNOREDIRS += notes/atomic
IGNOREDIRS += notes/bb
IGNOREDIRS += notes/phy1530
#IGNOREDIRS += notes/phy487 # hack:
#D:\peeterj\Peeter_cygwinHome\physicsplay\notes\phy487\condensedMatterProblemSet8Problem1.tex:400: LaTeX Error: File `../../figures/phy487/qmSolidsPs8dFig2' not found.
IGNOREDIRS += notes/gamma-matrix
SUBDIRS := $(filter-out $(IGNOREDIRS),$(SUBDIRS))

GITIGNORES := $(addsuffix /.gitignore,$(SUBDIRS))

ALLNOTES += notes/gabook/gabook.pdf
#ALLNOTES += notes/miscphysics/miscphysics.pdf
ALLNOTES += notes/classicalmechanics/classicalmechanics.pdf
#ALLNOTES += notes/dekker/dekker.pdf
#ALLNOTES += notes/papers/relwave.pdf
ALLNOTES += notes/phy356/phy356.pdf
#ALLNOTES += notes/phy356/desaiTypos.pdf
ALLNOTES += notes/phy450/phy450.pdf
#ALLNOTES += notes/papers/gramSchmidtLorentz.pdf
ALLNOTES += notes/phy456/phy456.pdf
ALLNOTES += notes/phy454/phy454.pdf
ALLNOTES += notes/phy485/phy485.pdf
ALLNOTES += notes/phy452/phy452.pdf
ALLNOTES += notes/phy487/phy487.pdf

all :: .gitignore subdirs

e:
	echo s: $(SUBMAKES)
	echo s: $(SUBDIRS)
	echo g: $(GITIGNORES)

allnotes.pdf : $(ALLNOTES)
	pdftk $(ALLNOTES) cat output $@

.PHONY: subdirs #$(SUBDIRS)

subdirs:
	$(foreach dir,$(SUBDIRS),make -C $(dir);)

%/.gitignore : %/GNUmakefile
	make -C $(<D) .gitignore

.gitignore : .gitignore.in $(GITIGNORES)
	cat $^ > $@
