#PRODUCTION := 1
#PROFILED := 1

include ../make.vars

#CXXFLAGS += -D_GLIBCXX_USE_CXX11_ABI=0

THISDIR := phy1610/silo

ifneq ("$(OSNAME)","Cygwin")
   TEST_LDLIBS += $(BOOST_TEST_LDLIBS)
endif
LDLIBS += -lsiloh5

TARGETS += example1
EXAMPLE1_SOURCES := example1.cc
EXAMPLE1_OBJECTS := $(subst .cc,.o,$(EXAMPLE1_SOURCES))

TARGETS += example_timestep
EXAMPLE_TIMESTEP_SOURCES := example_timestep.cc
EXAMPLE_TIMESTEP_OBJECTS := $(subst .cc,.o,$(EXAMPLE_TIMESTEP_SOURCES))

TARGETS += dartmouth
#TARGETS += temp.dat
#TARGETS += wind_vel.dat
DARTMOUTH_SOURCES := dartmouth.cc
DARTMOUTH_OBJECTS := $(subst .cc,.o,$(DARTMOUTH_SOURCES))

CLEANTARGETS += $(TARGETS)

# doxygen:
all : $(TARGETS)

#temp.dat : mktemp
#	./$^ > $@
#
#wind_vel.dat : mkvel
#	./$^ > $@

dartmouth : $(DARTMOUTH_OBJECTS)
	$(CXX) -o $@ $(DARTMOUTH_OBJECTS) $(LDFLAGS) $(DARTMOUTH_LDFLAGS) $(LDLIBS) $(DARTMOUTH_LDLIBS)

example1 : $(EXAMPLE1_OBJECTS)
	$(CXX) -o $@ $(EXAMPLE1_OBJECTS) $(LDFLAGS) $(EXAMPLE1_LDFLAGS) $(LDLIBS) $(EXAMPLE1_LDLIBS)

example_timestep : $(EXAMPLE_TIMESTEP_OBJECTS)
	$(CXX) -o $@ $(EXAMPLE_TIMESTEP_OBJECTS) $(LDFLAGS) $(EXAMPLE_TIMESTEP_LDFLAGS) $(LDLIBS) $(EXAMPLE_TIMESTEP_LDLIBS)

include ../make.rules
