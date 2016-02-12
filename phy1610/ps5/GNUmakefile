include ../make.vars

THISDIR := phy1610/ps5

GSL_LDLIBS += -lgsl
GSL_LDLIBS += -lgslcblas

ifneq ("$(OSNAME)","Cygwin")
   TEST_LDLIBS += $(BOOST_TEST_LDLIBS)
endif

TARGETS += springmodel
SPRINGMODEL_SOURCES += springmodel.cc
SPRINGMODEL_SOURCES += minimizer.cc
SPRINGMODEL_SOURCES += $(COMMON_SOURCES)
SPRINGMODEL_OBJECTS := $(subst .cc,.o,$(SPRINGMODEL_SOURCES))
SPRINGMODEL_LDLIBS += $(GSL_LDLIBS)

#TARGETS += test
#TEST_SOURCES += test.cc
#TEST_SOURCES += $(COMMON_SOURCES)
#TEST_OBJECTS := $(subst .cc,.o,$(TEST_SOURCES))
#TEST_LDLIBS += $(GSL_LDLIBS)

CLEANTARGETS += $(TARGETS)

# doxygen:
all : $(TARGETS)

springmodel : $(SPRINGMODEL_OBJECTS)
	$(CXX) -o $@ $(SPRINGMODEL_OBJECTS) $(SPRINGMODEL_LDLIBS)

#runtests: test
#	./test --report_level=detailed
#
#test : $(TEST_OBJECTS)
#	$(CXX) -o $@ $(TEST_OBJECTS) $(TEST_LDLIBS)

include ../make.rules
