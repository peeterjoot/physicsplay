#PRODUCTION := 1
#PROFILED := 1
#USETICKTOCK := 1

include ../make.vars
include ../make.netcdf.vars

CXXFLAGS += -I$(HOME)/rarray
ifdef SCINET_RARRAY_INC
   CXXFLAGS += -I$(SCINET_RARRAY_INC)
endif
CXXFLAGS += -I$(HOME)/ticktock

ifdef PROFILED
   # now only for origants.cc
   CXXFLAGS += -DNUMBER_OF_TIME_INTERVALS=400
endif
ifdef USETICKTOCK
   CXXFLAGS += -DUSE_TICK_TOCK

   # now only for origants.cc
   CXXFLAGS += -DNUMBER_OF_TIME_INTERVALS=400

   TEST_OBJECTS += ticktock.o
endif
#CXXFLAGS += -DMYRARRAY2_USE_STD_VECTOR
#CXXFLAGS += -DMYRARRAY_USING_RARRAY

THISDIR := phy1610/ps3

ifneq ("$(OSNAME)","Cygwin")
   TEST_LDLIBS += $(BOOST_TEST_LDLIBS)
endif

TARGETS += ants
TARGETS += origants
TARGETS += readants
ANTS_SOURCES += timestep.cc
ANTS_SOURCES += initialize.cc
ANTS_SOURCES += ants.cc
ifdef USETICKTOCK
ANTS_SOURCES += ticktock.cc
endif
ANTS_SOURCES += ants_on_table.cc
ANTS_SOURCES += output.cc
ANTS_SOURCES += $(COMMON_SOURCES)
ANTS_OBJECTS := $(subst .cc,.o,$(ANTS_SOURCES))

ORIGANTS_OBJECTS += origants.o 
ifdef USETICKTOCK
ORIGANTS_OBJECTS += ticktock.o 
endif

TARGETS += testdriver
TEST_SOURCES += ants_on_table.cc
TEST_SOURCES += timestep.cc
TEST_SOURCES += initialize.cc
TEST_SOURCES += testdriver.cc
TEST_SOURCES += $(COMMON_SOURCES)
TEST_OBJECTS += $(subst .cc,.o,$(TEST_SOURCES))

READANTS_SOURCES := readants.cc
READANTS_OBJECTS += $(subst .cc,.o,$(READANTS_SOURCES))

CLEANTARGETS += ants.out
CLEANTARGETS += antsTest.diff
CLEANTARGETS += gmon.out
CLEANTARGETS += orig.out
CLEANTARGETS += mine.out
CLEANTARGETS += profile.mine.txt
CLEANTARGETS += profile.orig.txt
CLEANTARGETS += $(TARGETS)

ALL_OBJECTS += $(ANTS_OBJECTS) $(TEST_OBJECTS) $(ORIGANTS_OBJECTS)

TARGETS += testarray
TESTARRAYOBJECTS += testarray.o 

all : $(TARGETS)

output.cc : ../inc/physicsplay_build_version.h

antsTest.diff: ants.out
	diff -up ../ps2/ants.out.default ants.out > $@

ants.out: ants
	./ants > $@

readants : $(READANTS_OBJECTS)
	$(CXX) $(LDFLAGS) -o $@ $(READANTS_OBJECTS) $(LDFLAGS) $(LDLIBS) $(READANTS_LDLIBS)

ants : $(ANTS_OBJECTS)
	$(CXX) $(LDFLAGS) -o $@ $(ANTS_OBJECTS) $(LDFLAGS) $(LDLIBS) $(ANTS_LDLIBS)

origants : $(ORIGANTS_OBJECTS)
	$(CXX) $(LDFLAGS) -o $@ $(ORIGANTS_OBJECTS) $(ANTS_LDLIBS)

test: runtestdriver runtestarray

runtestdriver:
	./testdriver --report_level=detailed

runtestarray:
	./testarray --report_level=detailed

testdriver : $(TEST_OBJECTS)
	$(CXX) $(LDFLAGS) -o $@ $(TEST_OBJECTS) $(TEST_LDLIBS)

testarray : $(TESTARRAYOBJECTS)
	$(CXX) $(LDFLAGS) -o $@ $(TESTARRAYOBJECTS) $(TEST_LDLIBS)

profile.mine.txt: ants
	rm -f gmon.out
	./ants -t 400 > mine.out
	$(GPROF) ./ants > $@

profile.orig.txt: origants
	rm -f gmon.out
	./origants > orig.out
	$(GPROF) ./origants > $@

include ../make.rules
