#PRODUCTION := 1
#PROFILED := 1
#USETICKTOCK := 1

include ../make.vars

THISDIR := phy1610-scientific-computing/ps5

GSL_LDLIBS += -lgsl
GSL_LDLIBS += -lgslcblas

ifneq ("$(OSNAME)","Cygwin")
   TEST_LDLIBS += $(BOOST_TEST_LDLIBS)
endif

TARGETS += springmodel
SPRINGMODEL_SOURCES += springmodel.cc
SPRINGMODEL_SOURCES += ../2015/ps5/solverMethod.cc
SPRINGMODEL_SOURCES += minimizer.cc
SPRINGMODEL_SOURCES += $(COMMON_SOURCES)
SPRINGMODEL_OBJECTS := $(subst .cc,.o,$(SPRINGMODEL_SOURCES))
SPRINGMODEL_LDLIBS += $(GSL_LDLIBS)

CLEANTARGETS += $(TARGETS)

all : $(TARGETS)

springmodel : $(SPRINGMODEL_OBJECTS)
	$(CXX) -o $@ $(SPRINGMODEL_OBJECTS) $(SPRINGMODEL_LDLIBS)

x.csv : springmodel
	./springmodel -m 0.1 > $@

include ../make.rules
