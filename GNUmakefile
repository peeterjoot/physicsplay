SUBMAKES := $(wildcard notes/*/GNUmakefile)

NOIGNORERULES += notes/atomic/GNUmakefile
NOIGNORERULES += notes/dekker/GNUmakefile
NOIGNORERULES += notes/gamma-matrix/GNUmakefile
NOIGNORERULES += notes/geometric-algebra/GNUmakefile
NOIGNORERULES += notes/phy1530/GNUmakefile
NOIGNORERULES += notes/phy354/GNUmakefile
NOIGNORERULES += notes/latex/GNUmakefile

SUBMAKES := $(filter-out $(NOIGNORERULES),$(SUBMAKES))

GITIGNORES := $(subst GNUmakefile,.gitignore,$(SUBMAKES))

all : .gitignore

%/.gitignore : %/GNUmakefile
	make -C $(<D) .gitignore

.gitignore : .gitignore.in $(GITIGNORES)
	cat $^ > $@
