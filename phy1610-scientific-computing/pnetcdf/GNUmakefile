#PRODUCTION := 1
#PROFILED := 1

include ../make.vars
#include ../make.vars.pnetcdf
#include ../make.vars.netcdf_c
include ../make.vars.mpi

CXXFLAGS += $(CXXFLAGS_NETCDF)

ifdef SCINET_NETCDF_INC
TARGETS += ncpar
endif
NCPAR_SOURCES += ncpar.cc
NCPAR_SOURCES += ../ps10/mpitask.cc
NCPAR_OBJECTS := $(subst .cc,.o,$(NCPAR_SOURCES))

LDLIBS += -lnetcdf -lhdf5 -lhdf5_hl -lcurl -lgpfs

CLEANTARGETS += $(TARGETS)
CLEANTARGETS += $(NCPAR_OBJECTS)
CLEANTARGETS += *.nc

all : $(TARGETS)

#writefile.o : ../inc/physicsplay_build_version.h

ncpar : $(NCPAR_OBJECTS)
	$(CXX) -o $@ $(NCPAR_OBJECTS) $(LDFLAGS) $(NCPAR_LDFLAGS) $(LDLIBS) $(NCPAR_LDLIBS)

include ../make.rules
