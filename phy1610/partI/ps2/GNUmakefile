# read in dependency files:
-include $(wildcard *.d)

OSNAME := $(shell uname -o)

#CXX := clang
# for windows (cygwin):
CXXFLAGS += -D_GLIBCXX_USE_C99

# generate dependency files with each compilation:
CXXFLAGS += -MMD

CXXFLAGS += -I../ps1

# PRODUCTION := 1

ifdef PRODUCTION
   CXXFLAGS += -DNDEBUG
   CXXFLAGS += -O2
else
   CXXFLAGS += -g
endif

CXXFLAGS += -std=c++11
THISDIR := phy1610/partI/ps2

#TARGETS += wave1dorig
TARGETS += wave1d
TARGETS += .gitignore
#TARGETS += waveparams.txt

WAVE1D_SOURCES += parameters.cc wave1d.cc
WAVE1D_OBJECTS := $(subst .cc,.o,$(WAVE1D_SOURCES))

all: $(TARGETS)

wave1d : $(WAVE1D_OBJECTS)
	$(CXX) -o $@ $(WAVE1D_OBJECTS)

CLEANTARGETS += $(TARGETS)
# doxygen:
CLEANTARGETS += html latex

# from run.sh
CLEANTARGETS += out0 out1

CLEANTARGETS += *.o

# clean dependency files if any
CLEANTARGETS += $(subst .cc,.d,$(wildcard *.cc))

.gitignore: GNUmakefile
	echo $(addprefix $(THISDIR)/,$(CLEANTARGETS)) | tr ' ' '\n' > $@

clean::
	rm -rf $(CLEANTARGETS)

#base:
#	wget https://support.scinet.utoronto.ca/education/get.php/wave1d.cc
#
#waveparams.txt:
#	wget https://support.scinet.utoronto.ca/education/get.php/waveparams.txt
