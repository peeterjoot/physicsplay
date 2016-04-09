#PRODUCTION := 1
#PROFILED := 1

include ../make.vars
#include ../make.vars.netcdf

CXXFLAGS += $(CXXFLAGS_NETCDF)

TARGETS += writefile
WRITEFILE_SOURCES += writefile.cc
WRITEFILE_OBJECTS := $(subst .cc,.o,$(WRITEFILE_SOURCES))
WRITEFILE_LDLIBS += -lnetcdf 
#WRITEFILE_LDLIBS += -lhdf5 -lhdf5_hl -lcurl -lgpfs

CLEANTARGETS += $(TARGETS)
CLEANTARGETS += *.nc

all : $(TARGETS)

writefile.cc : ../inc/physicsplay_build_version.h

writefile : $(WRITEFILE_OBJECTS)
	$(CXX) -o $@ $(WRITEFILE_OBJECTS) $(LDFLAGS) $(WRITEFILE_LDFLAGS) $(LDLIBS) $(WRITEFILE_LDLIBS)

include ../make.rules
