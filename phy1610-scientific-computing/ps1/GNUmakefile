THISDIR := phy1610-scientific-computing/ps1

#OSNAME := $(shell uname -o)

CXXFLAGS += -std=c++11
CXXFLAGS += -I../inc
CXXFLAGS += -Wall -Werror

# for windows (cygwin):
CXXFLAGS += -D_GLIBCXX_USE_C99

# generate dependency files with each compilation:
CXXFLAGS += -MMD

# PRODUCTION := 1
ifdef PRODUCTION
   CXXFLAGS += -DNDEBUG
   CXXFLAGS += -O2
else
   CXXFLAGS += -g
endif

TARGETS += lissajous.txt
TARGETS += lissajous
TARGETS += .gitignore

all: $(TARGETS)

CLEANTARGETS += $(TARGETS)
# doxygen:
CLEANTARGETS += html latex

# clean dependency files if any
CLEANTARGETS += $(subst .cc,.d,$(wildcard *.cc))

.gitignore: GNUmakefile
	echo $(addprefix $(THISDIR)/,$(CLEANTARGETS)) | tr ' ' '\n' > $@

lissajous.txt : lissajous
	./lissajous > $@

clean::
	rm -rf $(CLEANTARGETS)

# read in dependency files:
-include $(wildcard *.d)
