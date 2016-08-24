#PRODUCTION := 1
#PROFILED := 1
#USE_OPENBLAS := 1

include ../../make.vars
include ../../make.vars.blas
include ../../make.vars.boosttest

CXXFLAGS += -I../../inc

ifneq ("$(OSNAME)","Cygwin")
   # don't have lapacke.h
   TARGETS += eigen
endif

EIGEN_SOURCES += eigen.cc
EIGEN_OBJECTS := $(subst .cc,.o,$(EIGEN_SOURCES))

ifeq ("$(shell uname)","Darwin")
   EIGEN_LDLIBS += -lblas -L/usr/local/Cellar/openblas/0.2.18/lib -llapack
else
   EIGEN_LDLIBS += -llapacke -lblas
endif

CLEANTARGETS += $(EIGEN_OBJECTS) $(TEST_OBJECTS)

CLEANTARGETS += $(TARGETS)

all : $(TARGETS)

eigen : $(EIGEN_OBJECTS)
	$(CXX) -o $@ $(EIGEN_OBJECTS) $(EIGEN_LDLIBS)

include ../../make.rules
