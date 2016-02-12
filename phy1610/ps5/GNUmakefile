OSNAME := $(shell uname -o)

# generate dependency files with each compilation:
CXXFLAGS += -MMD

CXXFLAGS += -I../inc

# PRODUCTION := 1
ifdef PRODUCTION
   CXXFLAGS += -DNDEBUG
   CXXFLAGS += -O2
else
   CXXFLAGS += -g
endif

CXXFLAGS += -Wall -Werror
CXXFLAGS += -std=c++11
THISDIR := phy1610/ps5

TARGETS += .gitignore

GSL_LDLIBS += -lgsl
GSL_LDLIBS += -lgslcblas

ifeq ("$(OSNAME)","Cygwin")
   CXXFLAGS += -D_GLIBCXX_USE_C99

   # get cxx11 abi link errors attempting to use boost unit_test with the pre-compiled boost library
   CXXFLAGS += -DUSE_SINGLE_HEADER_BOOST_TEST_FRAMEWORK

   # for putenv and mkstemp
   CXXFLAGS += -U__STRICT_ANSI__
else
   TEST_LDLIBS += -lboost_unit_test_framework
endif

TARGETS += springmodel
SPRINGMODEL_SOURCES += springmodel.cc
SPRINGMODEL_SOURCES += $(COMMON_SOURCES)
SPRINGMODEL_OBJECTS := $(subst .cc,.o,$(SPRINGMODEL_SOURCES))
SPRINGMODEL_LDLIBS += $(GSL_LDLIBS)

#TARGETS += test
#TEST_SOURCES += test.cc
#TEST_SOURCES += $(COMMON_SOURCES)
#TEST_OBJECTS := $(subst .cc,.o,$(TEST_SOURCES))
#TEST_LDLIBS += $(GSL_LDLIBS)

CLEANTARGETS += $(TARGETS)
# doxygen:
CLEANTARGETS += html latex

# clean dependency and object files if any
CLEANTARGETS += *.o
CLEANTARGETS += *.d

all : $(TARGETS)

springmodel : $(SPRINGMODEL_OBJECTS)
	$(CXX) -o $@ $(SPRINGMODEL_OBJECTS) $(SPRINGMODEL_LDLIBS)

#runtests: test
#	./test --report_level=detailed
#
#test : $(TEST_OBJECTS)
#	$(CXX) -o $@ $(TEST_OBJECTS) $(TEST_LDLIBS)

.gitignore: GNUmakefile
	echo $(addprefix $(THISDIR)/,$(CLEANTARGETS)) | tr ' ' '\n' > $@

clean::
	rm -rf $(CLEANTARGETS)

# read in dependency files:
-include $(wildcard *.d)
