PRODUCTION := 1
#PROFILED := 1
#USETICKTOCK := 1

include ../make.vars

THISDIR := phy1610-scientific-computing/vt

ifneq ("$(OSNAME)","Cygwin")
   TEST_LDLIBS += $(BOOST_TEST_LDLIBS)
endif

TARGETS += vt
VT_SOURCES += vt.cc
VT_OBJECTS := $(subst .cc,.o,$(VT_SOURCES))

CLEANTARGETS += $(TARGETS)

ALL_OBJECTS += $(VT_OBJECTS) $(TEST_OBJECTS)

all : $(TARGETS)

vt : $(VT_OBJECTS)
	$(CXX) $(LDFLAGS) -o $@ $(VT_OBJECTS) $(VT_LDLIBS)

origvt : $(ORIGVT_OBJECTS)
	$(CXX) $(LDFLAGS) -o $@ $(ORIGVT_OBJECTS) $(VT_LDLIBS)

test: runtestdriver

runtestdriver:
	./testdriver --report_level=detailed

testdriver : $(TEST_OBJECTS)
	$(CXX) $(LDFLAGS) -o $@ $(TEST_OBJECTS) $(TEST_LDLIBS)

include ../make.rules
