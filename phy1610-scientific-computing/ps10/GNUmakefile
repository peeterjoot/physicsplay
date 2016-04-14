#
# Makefile for 1dwave code for SciNet's High Performance Scientific Computing
#  
# Modules required
#
#module load gcc/4.8.1
#module load pgplot/5.2.2-gcc

#PRODUCTION := 1
#PROFILED := 1

#CXXSTD := -std=c++11
CXX := mpic++

include ../make.vars
include ../make.vars.rarray
include ../make.vars.boosttest
include ../make.vars.mpi
include ../make.vars.pnetcdf

CXXFLAGS += $(PGPLOT_CXXFLAGS)
CXXFLAGS += -I../inc

TARGETS += wave1d
WAVE1D_SOURCES += wave1d.cc
WAVE1D_SOURCES += sendAndRecieveGhostCells.cc
WAVE1D_SOURCES += ticktock.cc
WAVE1D_SOURCES += rangePartition.cc
WAVE1D_SOURCES += mpitask.cc
WAVE1D_SOURCES += netcdfIO.cc
WAVE1D_SOURCES += asciiIO.cc
WAVE1D_SOURCES += graphicsIO.cc
WAVE1D_SOURCES += iohandler.cc
WAVE1D_SOURCES += ../ps7/streamopen.cc
WAVE1D_OBJECTS := $(subst .cc,.o,$(WAVE1D_SOURCES))
WAVE1D_LDFLAGS += $(PGPLOT_LDFLAGS)
WAVE1D_LDLIBS += $(PGPLOT_LDLIBS)

TARGETS += test
TEST_SOURCES += test.cc
TEST_SOURCES += rangePartition.cc
TEST_OBJECTS := $(subst .cc,.o,$(TEST_SOURCES))
TEST_LDFLAGS += $(LDFLAGS_BOOSTTEST)
TEST_LDLIBS += $(LDLIBS_BOOSTTEST)

TARGETS += leftright
LEFTRIGHT_SOURCES += leftright.cc
LEFTRIGHT_OBJECTS := $(subst .cc,.o,$(LEFTRIGHT_SOURCES))

TARGETS += nocycle
NOCYCLE_SOURCES += nocycle.cc
NOCYCLE_OBJECTS := $(subst .cc,.o,$(NOCYCLE_SOURCES))

TARGETS += ghosts
GHOSTS_SOURCES += ghosts.cc
GHOSTS_SOURCES += sendAndRecieveGhostCells.cc
GHOSTS_OBJECTS := $(subst .cc,.o,$(GHOSTS_SOURCES))

TARGETS += iotest
IOTEST_SOURCES += iotest.cc
IOTEST_SOURCES += netcdfIO.cc
IOTEST_SOURCES += asciiIO.cc
IOTEST_SOURCES += graphicsIO.cc
IOTEST_SOURCES += iohandler.cc
IOTEST_SOURCES += rangePartition.cc
IOTEST_SOURCES += mpitask.cc
IOTEST_SOURCES += ../ps7/streamopen.cc
IOTEST_OBJECTS := $(subst .cc,.o,$(IOTEST_SOURCES))
IOTEST_LDFLAGS += $(PGPLOT_LDFLAGS)
IOTEST_LDLIBS += $(PGPLOT_LDLIBS)

TARGETS += readwavenc
READWAVENC_SOURCES += readwavenc.cc
READWAVENC_OBJECTS := $(subst .cc,.o,$(READWAVENC_SOURCES))

OUTCLEANTARGETS += *.nc
OUTCLEANTARGETS += *.out
OUTCLEANTARGETS += dataFilename*
OUTCLEANTARGETS += aggregate.out.*
OUTCLEANTARGETS += netcdf.out.*

CLEANTARGETS += $(TARGETS)
CLEANTARGETS += waveparams_*txt
CLEANTARGETS += $(OUTCLEANTARGETS)

all: $(TARGETS)

outclean:
	rm -f $(OUTCLEANTARGETS)

wave1d.o : ../inc/physicsplay_build_version.h

wave1d : $(WAVE1D_OBJECTS)
	$(CXX) -o $@ $(WAVE1D_OBJECTS) $(LDFLAGS) $(WAVE1D_LDFLAGS) $(LDLIBS) $(WAVE1D_LDLIBS)

iotest : $(IOTEST_OBJECTS)
	$(CXX) -o $@ $(IOTEST_OBJECTS) $(LDFLAGS) $(IOTEST_LDFLAGS) $(LDLIBS) $(IOTEST_LDLIBS)

leftright : $(LEFTRIGHT_OBJECTS)
	$(CXX) -o $@ $(LEFTRIGHT_OBJECTS) $(LDFLAGS) $(LEFTRIGHT_LDFLAGS) $(LDLIBS) $(LEFTRIGHT_LDLIBS)

nocycle : $(NOCYCLE_OBJECTS)
	$(CXX) -o $@ $(NOCYCLE_OBJECTS) $(LDFLAGS) $(NOCYCLE_LDFLAGS) $(LDLIBS) $(NOCYCLE_LDLIBS)

ghosts : $(GHOSTS_OBJECTS)
	$(CXX) -o $@ $(GHOSTS_OBJECTS) $(LDFLAGS) $(GHOSTS_LDFLAGS) $(LDLIBS) $(GHOSTS_LDLIBS)

test : $(TEST_OBJECTS)
	$(CXX) -o $@ $(TEST_OBJECTS) $(LDFLAGS) $(TEST_LDFLAGS) $(LDLIBS) $(TEST_LDLIBS)

readwavenc : $(READWAVENC_OBJECTS)
	$(CXX) -o $@ $(READWAVENC_OBJECTS) $(LDFLAGS) $(READWAVENC_LDFLAGS) $(LDLIBS) $(READWAVENC_LDLIBS)

runtest: test
	./test --report_level=detailed --log_level=all

include ../make.rules
