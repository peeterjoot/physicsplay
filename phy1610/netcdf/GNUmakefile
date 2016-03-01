#PRODUCTION := 1
#PROFILED := 1

include ../make.vars
include ../make.netcdf.vars

#CXXFLAGS += -D_GLIBCXX_USE_CXX11_ABI=0

THISDIR := phy1610/netcdf

ifneq ("$(OSNAME)","Cygwin")
   TEST_LDLIBS += $(BOOST_TEST_LDLIBS)
endif

TARGETS += writefile
WRITEFILE_SOURCES := writefile.cc
WRITEFILE_OBJECTS := $(subst .cc,.o,$(WRITEFILE_SOURCES))

TARGETS += readfile
READFILE_SOURCES := readfile.cc
READFILE_OBJECTS := $(subst .cc,.o,$(READFILE_SOURCES))

TARGETS += w2
W2_SOURCES := w2.cc
W2_OBJECTS := $(subst .cc,.o,$(W2_SOURCES))

#WRITEFILE_LDLIBS += -lnetcdf

#TARGETS += test
#TEST_SOURCES += test.cc
#TEST_SOURCES += $(COMMON_SOURCES)
#TEST_OBJECTS := $(subst .cc,.o,$(TEST_SOURCES))
#TEST_LDLIBS += $(GSL_LDLIBS)

CLEANTARGETS += $(TARGETS)
CLEANTARGETS += *.nc

# doxygen:
all : $(TARGETS)

readfile.cc writefile.cc : ../inc/physicsplay_build_version.h

w2 : $(W2_OBJECTS)
	$(CXX) -o $@ $(W2_OBJECTS) $(LDFLAGS) $(W2_LDFLAGS) $(LDLIBS) $(W2_LDLIBS)

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
