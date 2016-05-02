#PRODUCTION := 1
#PROFILED := 1
#USE_OPENBLAS := 1

include ../../make.vars
include ../../make.vars.boosttest
CXXFLAGS += -I../../inc

TARGETS += test
TARGETS += makethiswork
MAKETHISWORK_SOURCES += MyMatrix.cc makethiswork.cc
MAKETHISWORK_OBJECTS := $(subst .cc,.o,$(MAKETHISWORK_SOURCES))

TEST_LDLIBS += $(LDLIBS_BOOSTTEST)

TEST_SOURCES += MyMatrix.cc test.cc
TEST_OBJECTS := $(subst .cc,.o,$(TEST_SOURCES))

# from run.sh
CLEANTARGETS += out0 out1

CLEANTARGETS += *.o

CLEANTARGETS += a.ascii.dat
CLEANTARGETS += a.binary.dat

CLEANTARGETS += $(TARGETS)

all : $(TARGETS)

makethiswork : $(MAKETHISWORK_OBJECTS)
	$(CXX) -o $@ $(MAKETHISWORK_OBJECTS)

test : $(TEST_OBJECTS)
	$(CXX) -o $@ $(TEST_OBJECTS) $(LDFLAGS) $(TEST_LDLIBS)

include ../../make.rules
