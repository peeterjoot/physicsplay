OSNAME := $(shell uname -o)

# for windows (cygwin):
CXXFLAGS += -D_GLIBCXX_USE_C99

# generate dependency files with each compilation:
CXXFLAGS += -MMD

CXXFLAGS += -I../../inc

# PRODUCTION := 1
ifdef PRODUCTION
   CXXFLAGS += -DNDEBUG
   CXXFLAGS += -O2
else
   CXXFLAGS += -g
endif

CXXFLAGS += -Wall -Werror
CXXFLAGS += -std=c++11
THISDIR := phy1610/2015/ps5

TARGETS += .gitignore

GSL_LDLIBS += -lgsl
GSL_LDLIBS += -lgslcblas

ifeq ("$(OSNAME)","Cygwin")
   # get cxx11 abi link errors attempting to use boost unit_test with the pre-compiled boost library
   CXXFLAGS += -DUSE_SINGLE_HEADER_BOOST_TEST_FRAMEWORK

   # for putenv and mkstemp
   CXXFLAGS += -U__STRICT_ANSI__
else
   TEST_LDLIBS += -lboost_unit_test_framework
endif

TARGETS += showps5
DISPLAY_SOURCES += showps5.cc
DISPLAY_SOURCES += ps5function.cc
DISPLAY_OBJECTS := $(subst .cc,.o,$(DISPLAY_SOURCES))

COMMON_SOURCES += solverMethod.cc
COMMON_SOURCES += ps5function.cc
COMMON_SOURCES += squareRootTwoFunction.cc
COMMON_SOURCES += instantiations.cc
#COMMON_SOURCES += quadratic.cc

TARGETS += findroot
FINDROOT_SOURCES += findroot.cc
FINDROOT_SOURCES += $(COMMON_SOURCES)
FINDROOT_OBJECTS := $(subst .cc,.o,$(FINDROOT_SOURCES))
FINDROOT_LDLIBS += $(GSL_LDLIBS)

TARGETS += test
TEST_SOURCES += test.cc
TEST_SOURCES += $(COMMON_SOURCES)
TEST_OBJECTS := $(subst .cc,.o,$(TEST_SOURCES))
TEST_LDLIBS += $(GSL_LDLIBS)

CLEANTARGETS += $(TARGETS)
# doxygen:
CLEANTARGETS += html latex

CLEANTARGETS += $(FINDROOT_OBJECTS) $(TEST_OBJECTS)

# clean dependency files if any
CLEANTARGETS += $(subst .o,.d,$(TEST_OBJECTS) $(FINDROOT_OBJECTS))

all : $(TARGETS)

showps5 : $(DISPLAY_OBJECTS)
	$(CXX) -o $@ $(DISPLAY_OBJECTS) $(DISPLAY_LDLIBS)

findroot : $(FINDROOT_OBJECTS)
	$(CXX) -o $@ $(FINDROOT_OBJECTS) $(FINDROOT_LDLIBS)

runtests: test
	./test --report_level=detailed

test : $(TEST_OBJECTS)
	$(CXX) -o $@ $(TEST_OBJECTS) $(TEST_LDLIBS)

.gitignore: GNUmakefile
	echo $(addprefix $(THISDIR)/,$(CLEANTARGETS)) | tr ' ' '\n' > $@

clean::
	rm -rf $(CLEANTARGETS)

# read in dependency files:
-include $(wildcard *.d)
