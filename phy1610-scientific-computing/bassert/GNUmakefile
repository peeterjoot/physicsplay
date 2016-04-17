#PRODUCTION := 1
#PROFILED := 1
#USE_OPENBLAS := 1

include ../make.vars

TARGETS += bassert
BASSERT_SOURCES += bassert.cc
BASSERT_OBJECTS := $(subst .cc,.o,$(BASSERT_SOURCES))

CLEANTARGETS += $(TARGETS)

all : $(TARGETS)

bassert : $(BASSERT_OBJECTS)
	$(CXX) -o $@ $(BASSERT_OBJECTS) $(LDFLAGS) $(BASSERT_LDFLAGS) $(LDLIBS) $(BASSERT_LDLIBS)

include ../make.rules
