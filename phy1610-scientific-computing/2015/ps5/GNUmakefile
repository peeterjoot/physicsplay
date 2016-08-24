#PRODUCTION := 1
#PROFILED := 1
#USE_OPENBLAS := 1

include ../../make.vars
include ../../make.vars.boosttest

CXXFLAGS += -I../../inc

GSL_LDLIBS += -lgsl
GSL_LDLIBS += -lgslcblas

TEST_LDLIBS += $(LDLIBS_BOOSTTEST)

TARGETS += showps5
DISPLAY_SOURCES += showps5.cc
DISPLAY_SOURCES += ps5function.cc
DISPLAY_OBJECTS := $(subst .cc,.o,$(DISPLAY_SOURCES))

COMMON_SOURCES += solverMethod.cc
COMMON_SOURCES += ps5function.cc
COMMON_SOURCES += squareRootTwoFunction.cc
COMMON_SOURCES += instantiations.cc
#COMMON_SOURCES += quadratic.cc

TARGETS += findroot
FINDROOT_SOURCES += findroot.cc
FINDROOT_SOURCES += $(COMMON_SOURCES)
FINDROOT_OBJECTS := $(subst .cc,.o,$(FINDROOT_SOURCES))
FINDROOT_LDLIBS += $(GSL_LDLIBS)

TARGETS += test
TEST_SOURCES += test.cc
TEST_SOURCES += $(COMMON_SOURCES)
TEST_OBJECTS := $(subst .cc,.o,$(TEST_SOURCES))
TEST_LDLIBS += $(GSL_LDLIBS)

CLEANTARGETS += $(FINDROOT_OBJECTS) $(TEST_OBJECTS)

CLEANTARGETS += $(TARGETS)

all : $(TARGETS)

showps5 : $(DISPLAY_OBJECTS)
	$(CXX) -o $@ $(DISPLAY_OBJECTS) $(DISPLAY_LDLIBS)

findroot : $(FINDROOT_OBJECTS)
	$(CXX) -o $@ $(FINDROOT_OBJECTS) $(FINDROOT_LDLIBS)

runtests: test
	./test --report_level=detailed

test : $(TEST_OBJECTS)
	$(CXX) -o $@ $(TEST_OBJECTS) $(LDFLAGS) $(TEST_LDFLAGS) $(LDLIBS) $(TEST_LDLIBS)

include ../../make.rules
