SUBMAKES := $(wildcard notes/*/GNUmakefile)
#SUBMAKES := $(filter-out $(NOIGNORERULES),$(SUBMAKES))

GITIGNORES := $(subst GNUmakefile,.gitignore,$(SUBMAKES))

all : .gitignore

%/.gitignore : %/GNUmakefile
	make -C $(<D) .gitignore

.gitignore : .gitignore.in $(GITIGNORES)
	cat $^ > $@
