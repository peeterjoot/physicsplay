#PRODUCTION := 1
#PROFILED := 1

include ../make.vars

#THISDIR := phy1610-scientific-computing/fft

LDLIBS += -lfftw3 -lm

TARGETS += twoarrays
TWOARRAYS_SOURCES += twoarrays.cc
TWOARRAYS_SOURCES += parseArgs.cc
TWOARRAYS_OBJECTS := $(subst .cc,.o,$(TWOARRAYS_SOURCES))

TARGETS += inplace
INPLACE_SOURCES += inplace.cc
INPLACE_SOURCES += parseArgs.cc
INPLACE_OBJECTS := $(subst .cc,.o,$(INPLACE_SOURCES))

CLEANTARGETS += $(TARGETS)
CLEANTARGETS += *.csv *.pdf

all : $(TARGETS)

twoarrays : $(TWOARRAYS_OBJECTS)
	$(CXX) -o $@ $(TWOARRAYS_OBJECTS) $(LDFLAGS) $(TWOARRAYS_LDFLAGS) $(LDLIBS) $(TWOARRAYS_LDLIBS)

inplace : $(INPLACE_OBJECTS)
	$(CXX) -o $@ $(INPLACE_OBJECTS) $(LDFLAGS) $(INPLACE_LDFLAGS) $(LDLIBS) $(INPLACE_LDLIBS)

include ../make.rules
