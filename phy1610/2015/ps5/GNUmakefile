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

TARGETS += findroot
TARGETS += .gitignore
#TARGETS += waveparams.txt

#ifneq ("$(OSNAME)","Cygwin")
#   # get cxx11 abi link errors attempting to use boost unit_test
#   TARGETS += test
#endif

FINDROOT_SOURCES += findroot.cc
FINDROOT_OBJECTS := $(subst .cc,.o,$(FINDROOT_SOURCES))

FINDROOT_LDLIBS += -lgsl
FINDROOT_LDLIBS += -lgslcblas

#TEST_SOURCES += test.cc
#TEST_OBJECTS := $(subst .cc,.o,$(TEST_SOURCES))

CLEANTARGETS += $(TARGETS)
# doxygen:
CLEANTARGETS += html latex

CLEANTARGETS += $(FINDROOT_OBJECTS) $(TEST_OBJECTS)

# clean dependency files if any
CLEANTARGETS += $(subst .o,.d,$(TEST_OBJECTS) $(FINDROOT_OBJECTS))

all : $(TARGETS)

findroot : $(FINDROOT_OBJECTS)
	$(CXX) -o $@ $(FINDROOT_OBJECTS) $(FINDROOT_LDLIBS)

#test : $(TEST_OBJECTS)
#	$(CXX) -o $@ $(TEST_OBJECTS) -lboost_unit_test_framework

.gitignore: GNUmakefile
	echo $(addprefix $(THISDIR)/,$(CLEANTARGETS)) | tr ' ' '\n' > $@

clean::
	rm -rf $(CLEANTARGETS)

# read in dependency files:
-include $(wildcard *.d)
