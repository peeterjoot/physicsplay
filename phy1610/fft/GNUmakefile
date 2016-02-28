#PRODUCTION := 1
#PROFILED := 1

include ../make.vars

THISDIR := phy1610/fft
#CXXFLAGS += -E

ifneq ("$(OSNAME)","Cygwin")
   TEST_LDLIBS += $(BOOST_TEST_LDLIBS)
endif

TARGETS += example
FFT_SOURCES := example.cc
FFT_OBJECTS := $(subst .cc,.o,$(FFT_SOURCES))
FFT_LDLIBS += -lfftw3 -lm

#TARGETS += test
#TEST_SOURCES += test.cc
#TEST_SOURCES += $(COMMON_SOURCES)
#TEST_OBJECTS := $(subst .cc,.o,$(TEST_SOURCES))
#TEST_LDLIBS += $(GSL_LDLIBS)

CLEANTARGETS += $(TARGETS)
CLEANTARGETS += *.csv *.pdf

# doxygen:
all : $(TARGETS)

example : $(FFT_OBJECTS)
	$(CXX) -o $@ $(FFT_OBJECTS) $(FFT_LDLIBS)

#runtests: test
#	./test --report_level=detailed
#
#test : $(TEST_OBJECTS)
#	$(CXX) -o $@ $(TEST_OBJECTS) $(TEST_LDLIBS)

include ../make.rules
