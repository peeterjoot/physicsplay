#PRODUCTION := 1
#PROFILED := 1

include ../make.vars
#include ../make.vars.netcdf_c
include ../make.vars.pnetcdf
include ../make.vars.mpi

CXX := mpic++

LDLIBS += $(LDLIBS_PNETCDF)

TARGETS += writefile
WRITEFILE_SOURCES += writefile.cc
WRITEFILE_OBJECTS := $(subst .cc,.o,$(WRITEFILE_SOURCES))

TARGETS += writefilep
WRITEFILEP_SOURCES += writefilep.cc
WRITEFILEP_SOURCES += ../ps10/mpitask.cc
WRITEFILEP_SOURCES += ../ps10/rangePartition.cc
WRITEFILEP_OBJECTS := $(subst .cc,.o,$(WRITEFILEP_SOURCES))
#WRITEFILEP_LDLIBS += -lnetcdf -lhdf5 -lhdf5_hl -lcurl -lgpfs

CLEANTARGETS += $(TARGETS)
CLEANTARGETS += $(WRITEFILEP_OBJECTS)
CLEANTARGETS += *.nc

all : $(TARGETS)

writefilep.cc writefile.cc : ../inc/physicsplay_build_version.h

writefile : $(WRITEFILE_OBJECTS)
	$(CXX) -o $@ $(WRITEFILE_OBJECTS) $(LDFLAGS) $(WRITEFILE_LDFLAGS) $(LDLIBS) $(WRITEFILE_LDLIBS)

writefilep : $(WRITEFILEP_OBJECTS)
	$(CXX) -o $@ $(WRITEFILEP_OBJECTS) $(LDFLAGS) $(WRITEFILEP_LDFLAGS) $(LDLIBS) $(WRITEFILEP_LDLIBS)

include ../make.rules
