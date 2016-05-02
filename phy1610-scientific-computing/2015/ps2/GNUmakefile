#PRODUCTION := 1
#PROFILED := 1
#USE_OPENBLAS := 1

include ../../make.vars
CXXFLAGS += -I../../inc

TARGETS += wave1d
WAVE1D_SOURCES += parameters.cc wave1d.cc
WAVE1D_OBJECTS := $(subst .cc,.o,$(WAVE1D_SOURCES))

CLEANTARGETS += $(TARGETS)

all : $(TARGETS)

wave1d : $(WAVE1D_OBJECTS)
	$(CXX) -o $@ $(WAVE1D_OBJECTS)

include ../../make.rules
