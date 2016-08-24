#PRODUCTION := 1
#PROFILED := 1
#USE_OPENBLAS := 1

include ../../make.vars

CXXFLAGS += -I../../inc
CXXFLAGS += -I../ps3

ifneq ("$(OSNAME)","Darwin")
TARGETS += profile.txt
endif
TARGETS += mm

MM_SOURCES += mm.cc ../ps3/MyMatrix.cc mymultiply.cc ticktock.cc
MM_OBJECTS := $(subst .cc,.o,$(MM_SOURCES))

CLEANTARGETS += $(MM_OBJECTS)
CLEANTARGETS += profile.txt
CLEANTARGETS += *.dat

CLEANTARGETS += $(TARGETS)

all : $(TARGETS)

mm : $(MM_OBJECTS)
	$(CXX) -o $@ $(MM_OBJECTS) $(LDFLAGS)

profile: profile.txt
	@cat profile.txt

profile.txt: mm
	./mm > $@
	gprof --line ./mm >> $@

include ../../make.rules
