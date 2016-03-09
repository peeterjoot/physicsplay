#PRODUCTION := 1
#USE_OPENBLAS := 1

ifndef SCINET_OPENBLAS_INC
   ifdef USE_OPENBLAS
      # ubuntu libopenblas
      CXXFLAGS += -I/usr/include/openblas
      LDFLAGS += -L/usr/lib/openblas
      LDFLAGS += -lopenblas
   else
      # ubuntu libblas
      LDFLAGS += -lblas
   endif
endif

include ../make.vars

#CXXFLAGS += -DRARRAY_USE_ALLOC_ALIGNED16

ifdef SCINET_RARRAY_INC
   CXXFLAGS += -I$(SCINET_RARRAY_INC)
else
   CXXFLAGS += -I$(HOME)/rarray
endif
CXXFLAGS += -DRATPATH=\"$(HOME)/gravitationalwaves\"

THISDIR := phy1610-scientific-computing/ps7

ifneq ("$(OSNAME)","Cygwin")
   TEST_LDLIBS += $(BOOST_TEST_LDLIBS)
endif

TARGETS += grav
GRAV_SOURCES += grav.cc
GRAV_SOURCES += ratData.cc
GRAV_SOURCES += fftstate.cc
GRAV_SOURCES += dotprod.cc
GRAV_SOURCES += streamopen.cc
GRAV_OBJECTS := $(subst .cc,.o,$(GRAV_SOURCES))
GRAV_LDLIBS += -lfftw3 -lm

TARGETS += ratToCsv
RATTOCSV_SOURCES += ratToCsv.cc
RATTOCSV_SOURCES += ratData.cc
RATTOCSV_SOURCES += streamopen.cc
RATTOCSV_SOURCES += swapFileNameSuffix.cc
RATTOCSV_OBJECTS := $(subst .cc,.o,$(RATTOCSV_SOURCES))

#TARGETS += booste
BOOSTE_SOURCES += booste.cc
BOOSTE_OBJECTS := $(subst .cc,.o,$(BOOSTE_SOURCES))

TARGETS += test
TEST_SOURCES += test.cc
TEST_SOURCES += swapFileNameSuffix.cc
TEST_SOURCES += streamopen.cc
TEST_SOURCES += dotprod.cc
TEST_OBJECTS := $(subst .cc,.o,$(TEST_SOURCES))

CLEANTARGETS += $(TARGETS)
CLEANTARGETS += *.o
CLEANTARGETS += *.pdf
CLEANTARGETS += *.csv

all : $(TARGETS)

grav : $(GRAV_OBJECTS)
	$(CXX) -o $@ $(GRAV_OBJECTS) $(LDFLAGS) $(GRAV_LDFLAGS) $(LDLIBS) $(GRAV_LDLIBS)

ratToCsv : $(RATTOCSV_OBJECTS)
	$(CXX) -o $@ $(RATTOCSV_OBJECTS) $(LDFLAGS) $(RATTOCSV_LDFLAGS) $(LDLIBS) $(RATTOCSV_LDLIBS)

booste : $(BOOSTE_OBJECTS)
	$(CXX) -o $@ $(BOOSTE_OBJECTS) $(LDFLAGS) $(BOOSTE_LDFLAGS) $(LDLIBS) $(BOOSTE_LDLIBS)

test : $(TEST_OBJECTS)
	$(CXX) -o $@ $(TEST_OBJECTS) $(LDFLAGS) $(TEST_LDFLAGS) $(LDLIBS) $(TEST_LDLIBS)

#grav.cc : ../inc/physicsplay_build_version.h

runtestdriver: test
	./test --report_level=detailed

include ../make.rules
