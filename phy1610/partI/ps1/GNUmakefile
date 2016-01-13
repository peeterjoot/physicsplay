CXXFLAGS += -std=c++11
THISDIR := phy1610/partI/ps1

OSNAME := $(shell uname -o)

#CXX := clang
# for windows (cygwin):
CXXFLAGS += -D_GLIBCXX_USE_C99

# generate dependency files with each compilation:
CXXFLAGS += -MMD

CXXFLAGS += -Wall

# PRODUCTION := 1

ifdef PRODUCTION
   CXXFLAGS += -DNDEBUG
   CXXFLAGS += -O2
else
   CXXFLAGS += -g
endif

TARGETS += tanhTable
TARGETS += .gitignore

all: $(TARGETS)

CLEANTARGETS += $(TARGETS)
# doxygen:
CLEANTARGETS += html latex

# clean dependency files if any
CLEANTARGETS += $(subst .cc,.d,$(wildcard *.cc))

.gitignore: GNUmakefile
	echo $(addprefix $(THISDIR)/,$(CLEANTARGETS)) | tr ' ' '\n' > $@

clean::
	rm -rf $(CLEANTARGETS)

# read in dependency files:
-include $(wildcard *.d)
