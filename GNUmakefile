SUBMAKES += $(wildcard notes/*/GNUmakefile)
SUBMAKES += $(wildcard phy1610-scientific-computing/*/GNUmakefile)
SUBMAKES += $(wildcard phy1610-scientific-computing/*/*/GNUmakefile)
SUBDIRS := $(subst /GNUmakefile,,$(SUBMAKES))
IGNOREDIRS += notes/atomic
IGNOREDIRS += notes/bb
IGNOREDIRS += notes/peterlue
# not ready yet:
IGNOREDIRS += notes/phy2403-qft
IGNOREDIRS += notes/gamma-matrix
SUBDIRS := $(filter-out $(IGNOREDIRS),$(SUBDIRS))

GITIGNORES := $(addsuffix /.gitignore,$(SUBDIRS))

ALLNOTES += notes/gabookI/gabookI.pdf
ALLNOTES += notes/gabookII/gabookII.pdf
ALLNOTES += notes/miscphysics/miscphysics.pdf
ALLNOTES += notes/classicalmechanics/classicalmechanics.pdf
#ALLNOTES += notes/dekker/dekker.pdf
ALLNOTES += notes/papers/relwave.pdf
ALLNOTES += notes/phy356-qmI/phy356.pdf
#ALLNOTES += notes/phy356/desaiTypos.pdf
ALLNOTES += notes/phy450-relativisticEandM/phy450.pdf
ALLNOTES += notes/papers/gramSchmidtLorentz.pdf
ALLNOTES += notes/phy456-qmII/phy456.pdf
ALLNOTES += notes/phy454-continuumechanics/phy454.pdf
ALLNOTES += notes/phy485-optics/phy485.pdf
ALLNOTES += notes/phy452-basicstatmech/phy452.pdf
ALLNOTES += notes/phy487-qmsolids/phy487.pdf
ALLNOTES += notes/ece1254-multiphysics/ece1254.pdf
ALLNOTES += notes/ece1229-antenna/ece1229.pdf
ALLNOTES += notes/phy1520-quantum/phy1520.pdf
ALLNOTES += notes/ece1236-microwaves/phy1520.pdf

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

subclean:
	$(foreach dir,$(SUBDIRS),make -C $(dir) clean;)

%/.gitignore : %/GNUmakefile
	make -C $(<D) .gitignore

.gitignore : .gitignore.in $(GITIGNORES)
	cat $^ > $@
