PRODUCTION := 1
#PROFILED := 1

include ../make.vars
include ../make.vars.blas
include ../make.vars.rarray
include ../make.vars.boosttest

#THISDIR := phy1610-scientific-computing/ps8

TARGETS += diffring
DIFFRING_SOURCES += diffring.cc
DIFFRING_SOURCES += diffring_timestep.cc
DIFFRING_SOURCES += diffring_output.cc
DIFFRING_SOURCES += diffring_parameters.cc
DIFFRING_SOURCES += ticktock.cc
DIFFRING_SOURCES += sparkline.cc
DIFFRING_OBJECTS := $(subst .cc,.o,$(DIFFRING_SOURCES))

TARGETS += walkring
WALKRING_SOURCES += walkring.cc
WALKRING_SOURCES += ticktock.cc
WALKRING_SOURCES += sparkline.cc
WALKRING_SOURCES += walkring_output.cc
WALKRING_SOURCES += walkring_timestep.cc
WALKRING_SOURCES += walkring_parameters.cc
WALKRING_OBJECTS := $(subst .cc,.o,$(WALKRING_SOURCES))

TARGETS += test
TEST_SOURCES += test.cc
TEST_OBJECTS := $(subst .cc,.o,$(TEST_SOURCES))
TEST_LDFLAGS += $(LDFLAGS_BOOSTTEST)
TEST_LDLIBS += $(LDLIBS_BOOSTTEST)

CLEANTARGETS += $(TARGETS)

.PHONY: all clean run rundiffring runwalkring runtestdriver

all : $(TARGETS)

include ../make.rules

walkring : $(WALKRING_OBJECTS)
	$(CXX) -o $@ $(WALKRING_OBJECTS) $(LDFLAGS) $(WALKRING_LDFLAGS) $(LDLIBS) $(WALKRING_LDLIBS)

diffring : $(DIFFRING_OBJECTS)
	$(CXX) -o $@ $(DIFFRING_OBJECTS) $(LDFLAGS) $(DIFFRING_LDFLAGS) $(LDLIBS) $(DIFFRING_LDLIBS)

test : $(TEST_OBJECTS)
	$(CXX) -o $@ $(TEST_OBJECTS) $(LDFLAGS) $(TEST_LDFLAGS) $(LDLIBS) $(TEST_LDLIBS)

runtestdriver: test
	./test --report_level=detailed

run: rundiffring runwalkring

rundiffring: diffring diffring.ini
	./diffring diffring.ini

runwalkring: walkring walkring.ini
	./walkring walkring.ini
