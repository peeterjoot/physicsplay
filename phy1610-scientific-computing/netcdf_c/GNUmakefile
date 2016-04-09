#PRODUCTION := 1
#PROFILED := 1

include ../make.vars
#include ../make.vars.netcdf
include ../make.vars.netcdf_c
include ../make.vars.mpi

TARGETS += writefile
WRITEFILE_SOURCES += writefile.cc
WRITEFILE_OBJECTS := $(subst .cc,.o,$(WRITEFILE_SOURCES))

TARGETS += ncpar
NCPAR_SOURCES += ncpar.cc
NCPAR_SOURCES += ../ps10/mpitask.cc
NCPAR_OBJECTS := $(subst .cc,.o,$(NCPAR_SOURCES))
NCPAR_LDFLAGS += $(MPI_LDFLAGS)

CLEANTARGETS += $(TARGETS)
CLEANTARGETS += *.nc

all : $(TARGETS)

writefile.cc : ../inc/physicsplay_build_version.h

ncpar : $(NCPAR_OBJECTS)
	$(CXX) -o $@ $(NCPAR_OBJECTS) $(LDFLAGS) $(NCPAR_LDFLAGS) $(LDLIBS) $(NCPAR_LDLIBS)

writefile : $(WRITEFILE_OBJECTS)
	$(CXX) -o $@ $(WRITEFILE_OBJECTS) $(LDFLAGS) $(WRITEFILE_LDFLAGS) $(LDLIBS) $(WRITEFILE_LDLIBS)

include ../make.rules
