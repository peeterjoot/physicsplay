#PRODUCTION := 1
#PROFILED := 1

include ../make.vars

THISDIR := phy1610/fft

TARGETS += example
FFT_SOURCES := example.cc
FFT_OBJECTS := $(subst .cc,.o,$(FFT_SOURCES))
FFT_LDLIBS += -lfftw3 -lm

CLEANTARGETS += $(TARGETS)
CLEANTARGETS += *.csv *.pdf

# doxygen:
all : $(TARGETS)

example : $(FFT_OBJECTS)
	$(CXX) -o $@ $(FFT_OBJECTS) $(FFT_LDLIBS)

include ../make.rules
