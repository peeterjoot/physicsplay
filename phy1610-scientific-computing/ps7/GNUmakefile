PRODUCTION := 1
#PROFILED := 1
#USE_OPENBLAS := 1

include ../make.vars.blas
include ../make.vars.rarray
include ../make.vars.fftw
include ../make.vars.boosttest
include ../make.vars

#CXXFLAGS += -DRARRAY_USE_ALLOC_ALIGNED16

CXXFLAGS += -DRATPATH=\"$(HOME)/gravitationalwaves\"

THISDIR := phy1610-scientific-computing/ps7

TARGETS += grav
GRAV_SOURCES += grav.cc
GRAV_SOURCES += ratData.cc
GRAV_SOURCES += fftstate.cc
GRAV_SOURCES += dotprod.cc
GRAV_SOURCES += streamopen.cc
GRAV_OBJECTS := $(subst .cc,.o,$(GRAV_SOURCES))
GRAV_LDLIBS += $(FFTW_LDLIBS)

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

profile.txt: grav
	rm -f gmon.out
	./grav > grav.out
	$(GPROF) ./grav > $@

include ../make.rules
