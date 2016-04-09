#PRODUCTION := 1
#PROFILED := 1

include ../make.vars
#include ../make.vars.netcdf

TARGETS += writefile
WRITEFILE_SOURCES += writefile.cc
WRITEFILE_OBJECTS := $(subst .cc,.o,$(WRITEFILE_SOURCES))

CLEANTARGETS += $(TARGETS)
CLEANTARGETS += *.nc

all : $(TARGETS)

writefile : $(WRITEFILE_OBJECTS)
	$(CXX) -o $@ $(WRITEFILE_OBJECTS) $(LDFLAGS) $(WRITEFILE_LDFLAGS) $(LDLIBS) $(WRITEFILE_LDLIBS)

include ../make.rules
