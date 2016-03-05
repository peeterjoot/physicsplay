#PRODUCTION := 1

include ../make.vars

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
GRAV_SOURCES := grav.cc
GRAV_OBJECTS := $(subst .cc,.o,$(GRAV_SOURCES))

TARGETS += rarrayiotest
RARRAYIOTEST_SOURCES := rarrayiotest.cc
RARRAYIOTEST_OBJECTS := $(subst .cc,.o,$(RARRAYIOTEST_SOURCES))

CLEANTARGETS += $(TARGETS)
CLEANTARGETS += *.o

all : $(TARGETS)

grav : $(GRAV_OBJECTS)
	$(CXX) -o $@ $(GRAV_OBJECTS) $(LDFLAGS) $(GRAV_LDFLAGS) $(LDLIBS) $(GRAV_LDLIBS)

rarrayiotest : $(RARRAYIOTEST_OBJECTS)
	$(CXX) -o $@ $(RARRAYIOTEST_OBJECTS) $(LDFLAGS) $(RARRAYIOTEST_LDFLAGS) $(LDLIBS) $(RARRAYIOTEST_LDLIBS)

#grav.cc : ../inc/physicsplay_build_version.h

#runtestdriver:
#	./testdriver --report_level=detailed

include ../make.rules
