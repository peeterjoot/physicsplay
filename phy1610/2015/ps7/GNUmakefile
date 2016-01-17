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
THISDIR := phy1610/2015/ps7

TARGETS += eigen
TARGETS += .gitignore
#TARGETS += waveparams.txt

#ifneq ("$(OSNAME)","Cygwin")
#   # get cxx11 abi link errors attempting to use boost unit_test
#   TARGETS += test
#endif

EIGEN_SOURCES += eigen.cc
EIGEN_OBJECTS := $(subst .cc,.o,$(EIGEN_SOURCES))

EIGEN_LDLIBS += -llapacke -lblas

#EIGEN_LDLIBS += -lgsl
#EIGEN_LDLIBS += -lgslcblas

#ifeq ("$(OSNAME)","Cygwin")
#   # get cxx11 abi link errors attempting to use boost unit_test with the pre-compiled boost library
#   CXXFLAGS += -DUSE_SINGLE_HEADER_BOOST_TEST_FRAMEWORK
#
#   # for putenv and mkstemp
#   CXXFLAGS += -U__STRICT_ANSI__
#else
#   TEST_LDLIBS += -lboost_unit_test_framework
#endif
#TARGETS += test

#TEST_SOURCES += test.cc
#TEST_OBJECTS := $(subst .cc,.o,$(TEST_SOURCES))

CLEANTARGETS += $(TARGETS)
# doxygen:
CLEANTARGETS += html latex

CLEANTARGETS += $(EIGEN_OBJECTS) $(TEST_OBJECTS)

# clean dependency files if any
CLEANTARGETS += $(subst .o,.d,$(TEST_OBJECTS) $(EIGEN_OBJECTS))

all : $(TARGETS)

eigen : $(EIGEN_OBJECTS)
	$(CXX) -o $@ $(EIGEN_OBJECTS) $(EIGEN_LDLIBS)

#test : $(TEST_OBJECTS)
#	$(CXX) -o $@ $(TEST_OBJECTS) $(TEST_LDLIBS)

.gitignore: GNUmakefile
	echo $(addprefix $(THISDIR)/,$(CLEANTARGETS)) | tr ' ' '\n' > $@

clean::
	rm -rf $(CLEANTARGETS)

# read in dependency files:
-include $(wildcard *.d)
