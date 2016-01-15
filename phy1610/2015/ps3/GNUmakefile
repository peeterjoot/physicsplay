OSNAME := $(shell uname -o)

# for windows (cygwin):
CXXFLAGS += -D_GLIBCXX_USE_C99

# generate dependency files with each compilation:
CXXFLAGS += -MMD

#CXXFLAGS += -DWITH_ARRAY

CXXFLAGS += -I../../inc

# PRODUCTION := 1
ifdef PRODUCTION
   CXXFLAGS += -DNDEBUG
   CXXFLAGS += -O2
else
   CXXFLAGS += -g
endif

CXXFLAGS += -Wall -Werror
CXXFLAGS += -std=c++11
THISDIR := phy1610/2015/ps3

#TARGETS += makethisworkorig
TARGETS += makethiswork
TARGETS += .gitignore
#TARGETS += waveparams.txt

ifneq ("$(OSNAME)","Cygwin")
   # get cxx11 abi link errors attempting to use boost unit_test
   TARGETS += test
endif

MAKETHISWORK_SOURCES += MyMatrix.cc makethiswork.cc
MAKETHISWORK_OBJECTS := $(subst .cc,.o,$(MAKETHISWORK_SOURCES))

TEST_SOURCES += MyMatrix.cc test.cc
TEST_OBJECTS := $(subst .cc,.o,$(TEST_SOURCES))

CLEANTARGETS += $(TARGETS)
# doxygen:
CLEANTARGETS += html latex

# from run.sh
CLEANTARGETS += out0 out1

CLEANTARGETS += *.o

CLEANTARGETS += a.ascii.dat
CLEANTARGETS += a.binary.dat

# clean dependency files if any
CLEANTARGETS += $(subst .cc,.d,$(wildcard *.cc))

all : $(TARGETS)

makethiswork : $(MAKETHISWORK_OBJECTS)
	$(CXX) -o $@ $(MAKETHISWORK_OBJECTS)

test : $(TEST_OBJECTS)
	$(CXX) -o $@ $(TEST_OBJECTS) -lboost_unit_test_framework

.gitignore: GNUmakefile
	echo $(addprefix $(THISDIR)/,$(CLEANTARGETS)) | tr ' ' '\n' > $@

clean::
	rm -rf $(CLEANTARGETS)

# read in dependency files:
-include $(wildcard *.d)
