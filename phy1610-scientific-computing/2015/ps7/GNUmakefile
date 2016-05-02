#PRODUCTION := 1
#PROFILED := 1
#USE_OPENBLAS := 1

include ../../make.vars
include ../../make.vars.boosttest

CXXFLAGS += -I../../inc

ifneq ("$(OSNAME)","Cygwin")
   # don't have lapacke.h
   TARGETS += eigen
endif

EIGEN_SOURCES += eigen.cc
EIGEN_OBJECTS := $(subst .cc,.o,$(EIGEN_SOURCES))

EIGEN_LDLIBS += -llapacke -lblas

CLEANTARGETS += $(EIGEN_OBJECTS) $(TEST_OBJECTS)

CLEANTARGETS += $(TARGETS)

all : $(TARGETS)

eigen : $(EIGEN_OBJECTS)
	$(CXX) -o $@ $(EIGEN_OBJECTS) $(EIGEN_LDLIBS)

include ../../make.rules
