#PRODUCTION := 1
#PROFILED := 1
#USE_OPENBLAS := 1

include ../../make.vars
include ../../make.vars.boosttest

CXXFLAGS += -I../../inc

TARGETS += solveode

SOLVEODE_SOURCES += solveode.cc
SOLVEODE_OBJECTS := $(subst .cc,.o,$(SOLVEODE_SOURCES))

SOLVEODE_LDLIBS += -lgsl
SOLVEODE_LDLIBS += -lgslcblas

CLEANTARGETS += $(SOLVEODE_OBJECTS) $(TEST_OBJECTS)

CLEANTARGETS += $(TARGETS)

all : $(TARGETS)

solveode : $(SOLVEODE_OBJECTS)
	$(CXX) -o $@ $(SOLVEODE_OBJECTS) $(SOLVEODE_LDLIBS)

include ../../make.rules
