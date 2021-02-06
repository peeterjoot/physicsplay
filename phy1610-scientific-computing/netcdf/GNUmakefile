#PRODUCTION := 1
#PROFILED := 1

include ../make.vars
include ../make.vars.netcdf

#CXXFLAGS += -D_GLIBCXX_USE_CXX11_ABI=0

#THISDIR := phy1610-scientific-computing/netcdf

TARGETS += writefile
WRITEFILE_SOURCES += writefile.cc
WRITEFILE_OBJECTS := $(subst .cc,.o,$(WRITEFILE_SOURCES))

TARGETS += write3
WRITE3_SOURCES += write3.cc
WRITE3_OBJECTS := $(subst .cc,.o,$(WRITE3_SOURCES))

TARGETS += writefile2D
WRITEFILE_2D_SOURCES += writefile2D.cc
WRITEFILE_2D_OBJECTS := $(subst .cc,.o,$(WRITEFILE_2D_SOURCES))

TARGETS += readfile
READFILE_SOURCES += readfile.cc
READFILE_OBJECTS := $(subst .cc,.o,$(READFILE_SOURCES))

TARGETS += readfile2D
READFILE_2D_SOURCES += readfile2D.cc
READFILE_2D_OBJECTS := $(subst .cc,.o,$(READFILE_2D_SOURCES))

CLEANTARGETS += $(TARGETS)
CLEANTARGETS += *.nc

ifeq ("$(OSNAME)","Cygwin")
all : 
else
all : $(TARGETS)
endif

readfile.o writefile.o : ../inc/physicsplay_build_version.h
readfile2D.o writefile2D.o : ../inc/physicsplay_build_version.h

writefile : $(WRITEFILE_OBJECTS)
	$(CXX) -o $@ $(WRITEFILE_OBJECTS) $(LDFLAGS) $(WRITEFILE_LDFLAGS) $(LDLIBS) $(WRITEFILE_LDLIBS)

write3 : $(WRITE3_OBJECTS)
	$(CXX) -o $@ $(WRITE3_OBJECTS) $(LDFLAGS) $(WRITE3_LDFLAGS) $(LDLIBS) $(WRITE3_LDLIBS)

writefile2D : $(WRITEFILE_2D_OBJECTS)
	$(CXX) -o $@ $(WRITEFILE_2D_OBJECTS) $(LDFLAGS) $(WRITEFILE_2D_LDFLAGS) $(LDLIBS) $(WRITEFILE_2D_LDLIBS)

readfile : $(READFILE_OBJECTS)
	$(CXX) -o $@ $(READFILE_OBJECTS) $(LDFLAGS) $(READFILE_LDFLAGS) $(LDLIBS) $(READFILE_LDLIBS)

readfile2D : $(READFILE_2D_OBJECTS)
	$(CXX) -o $@ $(READFILE_2D_OBJECTS) $(LDFLAGS) $(READFILE_2D_LDFLAGS) $(LDLIBS) $(READFILE_2D_LDLIBS)

include ../make.rules
