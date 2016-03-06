#PRODUCTION := 1

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
GRAV_SOURCES += streamopen.cc
GRAV_SOURCES += swapFileNameSuffix.cc
GRAV_OBJECTS := $(subst .cc,.o,$(GRAV_SOURCES))

#TARGETS += booste
BOOSTE_SOURCES += booste.cc
BOOSTE_OBJECTS := $(subst .cc,.o,$(BOOSTE_SOURCES))

#TARGETS += rarrayiotest
RARRAYIOTEST_SOURCES += rarrayiotest.cc
RARRAYIOTEST_OBJECTS := $(subst .cc,.o,$(RARRAYIOTEST_SOURCES))

TARGETS += test
TEST_SOURCES += test.cc
TEST_SOURCES += swapFileNameSuffix.cc
TEST_OBJECTS := $(subst .cc,.o,$(TEST_SOURCES))

CLEANTARGETS += $(TARGETS)
CLEANTARGETS += *.o
CLEANTARGETS += *.pdf
CLEANTARGETS += *.csv

all : $(TARGETS)

grav : $(GRAV_OBJECTS)
	$(CXX) -o $@ $(GRAV_OBJECTS) $(LDFLAGS) $(GRAV_LDFLAGS) $(LDLIBS) $(GRAV_LDLIBS)

rarrayiotest : $(RARRAYIOTEST_OBJECTS)
	$(CXX) -o $@ $(RARRAYIOTEST_OBJECTS) $(LDFLAGS) $(RARRAYIOTEST_LDFLAGS) $(LDLIBS) $(RARRAYIOTEST_LDLIBS)

booste : $(BOOSTE_OBJECTS)
	$(CXX) -o $@ $(BOOSTE_OBJECTS) $(LDFLAGS) $(BOOSTE_LDFLAGS) $(LDLIBS) $(BOOSTE_LDLIBS)

test : $(TEST_OBJECTS)
	$(CXX) -o $@ $(TEST_OBJECTS) $(LDFLAGS) $(TEST_LDFLAGS) $(LDLIBS) $(TEST_LDLIBS)

#grav.cc : ../inc/physicsplay_build_version.h

runtestdriver: test
	./test --report_level=detailed

include ../make.rules
