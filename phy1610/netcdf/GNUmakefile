#PRODUCTION := 1
#PROFILED := 1

include ../make.vars

#CXXFLAGS += -D_GLIBCXX_USE_CXX11_ABI=0

THISDIR := phy1610/netcdf
ifdef SCINET_NETCDF_INC
   CXXFLAGS += -I$(SCINET_NETCDF_INC)
endif
ifdef SCINET_INTEL_INC
   CXXFLAGS += -wd858
endif

ifneq ("$(OSNAME)","Cygwin")
   TEST_LDLIBS += $(BOOST_TEST_LDLIBS)
endif

TARGETS += writefile
WRITEFILE_SOURCES := writefile.cc
WRITEFILE_OBJECTS := $(subst .cc,.o,$(WRITEFILE_SOURCES))

TARGETS += readfile
READFILE_SOURCES := readfile.cc
READFILE_OBJECTS := $(subst .cc,.o,$(READFILE_SOURCES))

ifdef SCINET_NETCDF_LIB
   LDFLAGS += -L$(SCINET_NETCDF_LIB)
endif

LDLIBS += -lnetcdf_c++4
#WRITEFILE_LDLIBS += -lnetcdf

#TARGETS += test
#TEST_SOURCES += test.cc
#TEST_SOURCES += $(COMMON_SOURCES)
#TEST_OBJECTS := $(subst .cc,.o,$(TEST_SOURCES))
#TEST_LDLIBS += $(GSL_LDLIBS)

CLEANTARGETS += $(TARGETS)
CLEANTARGETS += first.netCDF.nc

# doxygen:
all : $(TARGETS)

writefile : $(WRITEFILE_OBJECTS)
	$(CXX) -o $@ $(WRITEFILE_OBJECTS) $(LDFLAGS) $(WRITEFILE_LDFLAGS) $(LDLIBS) $(WRITEFILE_LDLIBS)

readfile : $(READFILE_OBJECTS)
	$(CXX) -o $@ $(READFILE_OBJECTS) $(LDFLAGS) $(READFILE_LDFLAGS) $(LDLIBS) $(READFILE_LDLIBS)

#runtests: test
#	./test --report_level=detailed
#
#test : $(TEST_OBJECTS)
#	$(CXX) -o $@ $(TEST_OBJECTS) $(TEST_LDLIBS)

include ../make.rules
