CXXFLAGS += -std=c++11
THISDIR := phy1610/partI/ps1

OSNAME := $(shell uname -o)

#CXX := clang
# for windows (cygwin):
CXXFLAGS += -D_GLIBCXX_USE_C99

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
