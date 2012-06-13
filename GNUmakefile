SUBMAKES := $(wildcard notes/*/GNUmakefile)
SUBDIRS := $(subst /GNUmakefile,,$(SUBMAKES))
IGNOREDIRS += notes/atomic
IGNOREDIRS += notes/bb
IGNOREDIRS += notes/phy1530
SUBDIRS := $(filter-out $(IGNOREDIRS),$(SUBDIRS))

GITIGNORES := $(addsuffix /.gitignore,$(SUBDIRS))

all :: .gitignore

e:
	echo s: $(SUBMAKES)
	echo s: $(SUBDIRS)
	echo g: $(GITIGNORES)

.PHONY: subdirs #$(SUBDIRS)

subdirs:
	$(foreach dir,$(SUBDIRS),make -C $(dir);)

%/.gitignore : %/GNUmakefile
	make -C $(<D) .gitignore

.gitignore : .gitignore.in $(GITIGNORES)
	cat $^ > $@
