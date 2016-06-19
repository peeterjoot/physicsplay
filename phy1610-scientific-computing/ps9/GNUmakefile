#
# Makefile for 1dwave code for SciNet's High Performance Scientific Computing
#  
# Modules required
#
#module load gcc/4.8.1
#module load pgplot/5.2.2-gcc

PRODUCTION := 1
#PROFILED := 1

CXX := mpic++
CXXSTD += -std=c++11

include ../make.vars
include ../make.vars.rarray
include ../make.vars.boosttest

CXXFLAGS += $(PGPLOT_CXXFLAGS)
CXXFLAGS += -I../inc

#
# mpic++ appears invoke clang on mac, and I don't find symbols like _omp_get_max_threads anywhere
# in the clang runtime.  See that there is a clang omp runtime extension, but it doesn't look like
# it's installed on my machine.  Can that be done after the fact, or does that have to be built-in?
# 
# Have hacked things to use gcc's omp runtime... probably doesn't work, but compiles and links.
#
ifeq ("$(OSNAME)","Darwin")
   CXXFLAGS += -I/usr/local/Cellar/gcc/5.3.0/lib/gcc/5/gcc/x86_64-apple-darwin15.0.0/5.3.0/include
   LDFLAGS += -L/usr/local/Cellar/gcc/5.3.0/lib/gcc/5
   LDLIBS += -lgomp
else
   CXXFLAGS += -fopenmp
   LDLIBS += -fopenmp
endif

# boost noisyness:
CXXFLAGS += -Wno-error=unused-local-typedefs
CXXFLAGS += -Wno-unused-local-typedefs

TARGETS += wave1d
WAVE1D_SOURCES += wave1d.cc
WAVE1D_SOURCES += arrayIOwriter.cc
WAVE1D_SOURCES += ticktock.cc
WAVE1D_OBJECTS := $(subst .cc,.o,$(WAVE1D_SOURCES))
WAVE1D_LDFLAGS += $(PGPLOT_LDFLAGS)
WAVE1D_LDLIBS += $(PGPLOT_LDLIBS)

TARGETS += test
TEST_SOURCES += test.cc
TEST_SOURCES += arrayIOwriter.cc
TEST_OBJECTS := $(subst .cc,.o,$(TEST_SOURCES))
TEST_LDFLAGS += $(LDFLAGS_BOOSTTEST)
TEST_LDLIBS += $(LDLIBS_BOOSTTEST)

TARGETS += metaToText
METATOTEXT_SOURCES += metaToText.cc
METATOTEXT_SOURCES += readem.cc
METATOTEXT_OBJECTS := $(subst .cc,.o,$(METATOTEXT_SOURCES))

TARGETS += dataToText
DATATOTEXT_SOURCES += dataToText.cc
DATATOTEXT_SOURCES += readem.cc
DATATOTEXT_OBJECTS := $(subst .cc,.o,$(DATATOTEXT_SOURCES))
ifdef  SCINET_BOOST_LIB_DIR
DATATOTEXT_LDFLAGS += -L$(SCINET_BOOST_LIB_DIR)
endif
DATATOTEXT_LDLIBS += -lboost_filesystem -lboost_system

CLEANTARGETS += $(TARGETS)
CLEANTARGETS += waveparams_*txt
CLEANTARGETS += $(wildcard [mst]all.out)
CLEANTARGETS += $(wildcard serial*out)
CLEANTARGETS += $(wildcard threaded*out)
CLEANTARGETS += $(wildcard multifile*out)
CLEANTARGETS += $(wildcard params* output* merged*)

all: $(TARGETS)

wave1d : $(WAVE1D_OBJECTS)
	$(CXX) -o $@ $(WAVE1D_OBJECTS) $(LDFLAGS) $(WAVE1D_LDFLAGS) $(LDLIBS) $(WAVE1D_LDLIBS)

metaToText : $(METATOTEXT_OBJECTS)
	$(CXX) -o $@ $(METATOTEXT_OBJECTS) $(LDFLAGS) $(METATOTEXT_LDFLAGS) $(LDLIBS) $(METATOTEXT_LDLIBS)

dataToText : $(DATATOTEXT_OBJECTS)
	$(CXX) -o $@ $(DATATOTEXT_OBJECTS) $(LDFLAGS) $(DATATOTEXT_LDFLAGS) $(LDLIBS) $(DATATOTEXT_LDLIBS)

test : $(TEST_OBJECTS)
	$(CXX) -o $@ $(TEST_OBJECTS) $(LDFLAGS) $(TEST_LDFLAGS) $(LDLIBS) $(TEST_LDLIBS)

CLEANTARGETS += $(TARGETS)
CLEANTARGETS += dataFilename*

all : $(TARGETS)

runtest: test
	./test --report_level=detailed --log_level=all

include ../make.rules
