#PRODUCTION := 1
#PROFILED := 1

# scinet setup for writefile, readfile: 
# ../scinet.env.netcdf.mpi.gcc-520
# ../scinet.env.netcdf.serial.gcc-520
#
# scinet setup for pwritefile: 
# ../scinet.env.netcdf.mpi.gcc-520

include ../make.vars
#include ../make.vars.netcdf_c
include ../make.vars.pnetcdf
# Not required with mpic++
#include ../make.vars.mpi

CXX := mpic++

LDLIBS += $(LDLIBS_PNETCDF)

TARGETS += writefile
WRITEFILE_SOURCES += writefile.cc
WRITEFILE_OBJECTS := $(subst .cc,.o,$(WRITEFILE_SOURCES))

TARGETS += readfile
READFILE_SOURCES += readfile.cc
READFILE_OBJECTS := $(subst .cc,.o,$(READFILE_SOURCES))

ifdef SCINET_NETCDF_INC
TARGETS += writefilep
endif
WRITEFILEP_SOURCES += writefilep.cc
WRITEFILEP_SOURCES += ../ps10/mpitask.cc
WRITEFILEP_SOURCES += ../ps10/rangePartition.cc
WRITEFILEP_OBJECTS := $(subst .cc,.o,$(WRITEFILEP_SOURCES))
#WRITEFILEP_LDLIBS += -lnetcdf -lhdf5 -lhdf5_hl -lcurl -lgpfs

CLEANTARGETS += $(TARGETS)
CLEANTARGETS += $(WRITEFILEP_OBJECTS)
CLEANTARGETS += *.nc

all : $(TARGETS)

writefilep.o writefile.o : ../inc/physicsplay_build_version.h

writefile : $(WRITEFILE_OBJECTS)
	$(CXX) -o $@ $(WRITEFILE_OBJECTS) $(LDFLAGS) $(WRITEFILE_LDFLAGS) $(LDLIBS) $(WRITEFILE_LDLIBS)

readfile : $(READFILE_OBJECTS)
	$(CXX) -o $@ $(READFILE_OBJECTS) $(LDFLAGS) $(READFILE_LDFLAGS) $(LDLIBS) $(READFILE_LDLIBS)

writefilep : $(WRITEFILEP_OBJECTS)
	$(CXX) -o $@ $(WRITEFILEP_OBJECTS) $(LDFLAGS) $(WRITEFILEP_LDFLAGS) $(LDLIBS) $(WRITEFILEP_LDLIBS)

include ../make.rules
