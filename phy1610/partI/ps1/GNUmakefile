CXXFLAGS += -std=c++11
THISDIR := phy1610/partI/ps1

OSNAME := $(shell uname -o)

ifeq ("$(OSNAME)", "Cygwin")
   # for c++11 support.  Not good enough: Turns out that the libstdc++ runtime and headers in cygwin (4.9.2) is also too old for "modern" C++ style used in this code.
   CXX := clang
endif

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

.gitignore: GNUmakefile
	echo $(addprefix $(THISDIR)/,$(CLEANTARGETS)) | tr ' ' '\n' > $@

clean::
	rm -rf $(CLEANTARGETS)
