SUBMAKES += $(wildcard notes/*/GNUmakefile)
SUBMAKES += $(wildcard phy1610/*/GNUmakefile)
SUBMAKES += $(wildcard phy1610/*/*/GNUmakefile)
SUBDIRS := $(subst /GNUmakefile,,$(SUBMAKES))
IGNOREDIRS += notes/atomic
IGNOREDIRS += notes/bb
IGNOREDIRS += notes/peterlue
# not ready yet:
IGNOREDIRS += notes/phy2403
IGNOREDIRS += notes/gamma-matrix
SUBDIRS := $(filter-out $(IGNOREDIRS),$(SUBDIRS))

GITIGNORES := $(addsuffix /.gitignore,$(SUBDIRS))

ALLNOTES += notes/gabookI/gabookI.pdf
ALLNOTES += notes/gabookII/gabookII.pdf
ALLNOTES += notes/miscphysics/miscphysics.pdf
ALLNOTES += notes/classicalmechanics/classicalmechanics.pdf
#ALLNOTES += notes/dekker/dekker.pdf
ALLNOTES += notes/papers/relwave.pdf
ALLNOTES += notes/phy356/phy356.pdf
#ALLNOTES += notes/phy356/desaiTypos.pdf
ALLNOTES += notes/phy450/phy450.pdf
ALLNOTES += notes/papers/gramSchmidtLorentz.pdf
ALLNOTES += notes/phy456/phy456.pdf
ALLNOTES += notes/phy454/phy454.pdf
ALLNOTES += notes/phy485/phy485.pdf
ALLNOTES += notes/phy452/phy452.pdf
ALLNOTES += notes/phy487/phy487.pdf
ALLNOTES += notes/ece1254/ece1254.pdf
ALLNOTES += notes/ece1229/ece1229.pdf
ALLNOTES += notes/phy1520/phy1520.pdf

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
