#
# Makefile for 1dwave code for SciNet's High Performance Scientific Computing
#  
# Modules required
#
#module load gcc/4.8.1
#module load pgplot/5.2.2-gcc

#PRODUCTION := 1
#PROFILED := 1

CXXSTD += -std=c++11
CXX := mpic++

include ../make.vars
include ../make.vars.rarray
#include ../make.vars.boosttest

CXXFLAGS += $(PGPLOT_CXXFLAGS)
#CXXFLAGS += -fopenmp
CXXFLAGS += -I../inc
CXXFLAGS += -Wno-error=literal-suffix
CXXFLAGS += -Wno-literal-suffix

# boost noisyness:
#CXXFLAGS += -Wno-error=unused-local-typedefs
#CXXFLAGS += -Wno-unused-local-typedefs

#LDLIBS += -fopenmp

TARGETS += wave1d
WAVE1D_SOURCES += wave1d.cc
#WAVE1D_SOURCES += arrayIOwriter.cc
WAVE1D_SOURCES += ticktock.cc
WAVE1D_OBJECTS := $(subst .cc,.o,$(WAVE1D_SOURCES))
WAVE1D_LDFLAGS += $(PGPLOT_LDFLAGS)
WAVE1D_LDLIBS += $(PGPLOT_LDLIBS)

#TARGETS += test
#TEST_SOURCES += test.cc
#TEST_SOURCES += arrayIOwriter.cc
#TEST_OBJECTS := $(subst .cc,.o,$(TEST_SOURCES))
#TEST_LDFLAGS += $(LDFLAGS_BOOSTTEST)
#TEST_LDLIBS += $(LDLIBS_BOOSTTEST)

CLEANTARGETS += $(TARGETS)
CLEANTARGETS += waveparams_*txt
CLEANTARGETS += dataFilename*

all: $(TARGETS)

wave1d : $(WAVE1D_OBJECTS)
	$(CXX) -o $@ $(WAVE1D_OBJECTS) $(LDFLAGS) $(WAVE1D_LDFLAGS) $(LDLIBS) $(WAVE1D_LDLIBS)

#test : $(TEST_OBJECTS)
#	$(CXX) -o $@ $(TEST_OBJECTS) $(LDFLAGS) $(TEST_LDFLAGS) $(LDLIBS) $(TEST_LDLIBS)

all : $(TARGETS)

runtest: test
	./test --report_level=detailed --log_level=all

include ../make.rules
