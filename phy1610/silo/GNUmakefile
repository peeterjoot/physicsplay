#PRODUCTION := 1
#PROFILED := 1

include ../make.vars

#CXXFLAGS += -D_GLIBCXX_USE_CXX11_ABI=0

THISDIR := phy1610/silo

ifneq ("$(OSNAME)","Cygwin")
   TEST_LDLIBS += $(BOOST_TEST_LDLIBS)
endif
LDLIBS += -lsiloh5

TARGETS += example
EXAMPLE_SOURCES := example.cc
EXAMPLE_OBJECTS := $(subst .cc,.o,$(EXAMPLE_SOURCES))

#TARGETS += test
#TEST_SOURCES += test.cc
#TEST_SOURCES += $(COMMON_SOURCES)
#TEST_OBJECTS := $(subst .cc,.o,$(TEST_SOURCES))

CLEANTARGETS += $(TARGETS)

# doxygen:
all : $(TARGETS)

example : $(EXAMPLE_OBJECTS)
	$(CXX) -o $@ $(EXAMPLE_OBJECTS) $(LDFLAGS) $(EXAMPLE_LDFLAGS) $(LDLIBS) $(EXAMPLE_LDLIBS)

#runtests: test
#	./test --report_level=detailed
#
#test : $(TEST_OBJECTS)
#	$(CXX) -o $@ $(TEST_OBJECTS) $(TEST_LDLIBS)

include ../make.rules
