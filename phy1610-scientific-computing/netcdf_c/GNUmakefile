#PRODUCTION := 1
#PROFILED := 1

include ../make.vars
include ../make.vars.netcdf_c

TARGETS += writefile
WRITEFILE_SOURCES += writefile.cc
WRITEFILE_OBJECTS := $(subst .cc,.o,$(WRITEFILE_SOURCES))

CLEANTARGETS += $(TARGETS)
CLEANTARGETS += *.nc

all : $(TARGETS)

writefile.cc : ../inc/physicsplay_build_version.h

writefile : $(WRITEFILE_OBJECTS)
	$(CXX) -o $@ $(WRITEFILE_OBJECTS) $(LDFLAGS) $(WRITEFILE_LDFLAGS) $(LDLIBS) $(WRITEFILE_LDLIBS)

include ../make.rules
