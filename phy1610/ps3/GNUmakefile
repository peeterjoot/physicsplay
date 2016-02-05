# generate dependency files with each compilation:
CXXFLAGS += -MMD

CXXFLAGS += -I../inc
CXXFLAGS += -I../ps2
CXXFLAGS += -I$(HOME)/rarray
ifdef SCINET_RARRAY_INC
   CXXFLAGS += -I$(SCINET_RARRAY_INC)
endif
CXXFLAGS += -I$(HOME)/ticktock

PRODUCTION := 1
#PROFILED := 1
#USETICKTOCK := 1
ifdef PRODUCTION
   CXXFLAGS += -DNDEBUG
   CXXFLAGS += -O2
else
   CXXFLAGS += -g
endif
ifdef PROFILED
   CXXFLAGS += -pg -g
   LDFLAGS += -pg -g
   CXXFLAGS += -DNUMBER_OF_TIME_INTERVALS=400
endif
ifdef USETICKTOCK
   CXXFLAGS += -DUSE_TICK_TOCK
   CXXFLAGS += -DNUMBER_OF_TIME_INTERVALS=400

   TEST_OBJECTS += ticktock.o
endif
#CXXFLAGS += -DMYRARRAY2_USE_STD_VECTOR
#CXXFLAGS += -DMYRARRAY_USING_RARRAY

CXXFLAGS += -Wall -Werror
CXXFLAGS += -std=c++11
THISDIR := phy1610/ps3

TARGETS += .gitignore

OSNAME := $(shell uname -o)
ifeq ("$(OSNAME)","Cygwin")
   CXXFLAGS += -D_GLIBCXX_USE_C99

   # get cxx11 abi link errors attempting to use boost unit_test with the pre-compiled boost library
   CXXFLAGS += -DUSE_SINGLE_HEADER_BOOST_TEST_FRAMEWORK

   # for putenv and mkstemp
   CXXFLAGS += -U__STRICT_ANSI__
else
   TEST_LDLIBS += -lboost_unit_test_framework
endif

TARGETS += ants
TARGETS += origants
ANTS_SOURCES += ../ps2/ants.cc
ANTS_SOURCES += ticktock.cc
ANTS_SOURCES += ../ps2/ants_on_table.cc
ANTS_SOURCES += $(COMMON_SOURCES)
ANTS_OBJECTS := $(subst .cc,.o,$(ANTS_SOURCES))

ORIGANTS_OBJECTS += origants.o 
ORIGANTS_OBJECTS += ticktock.o 

TARGETS += testdriver
TEST_SOURCES += ../ps2/ants_on_table.cc
TEST_SOURCES += testdriver.cc
TEST_SOURCES += $(COMMON_SOURCES)
TEST_OBJECTS += $(subst .cc,.o,$(TEST_SOURCES))

CLEANTARGETS += ants.out
CLEANTARGETS += antsTest.diff
CLEANTARGETS += gmon.out
CLEANTARGETS += orig.out
CLEANTARGETS += mine.out
CLEANTARGETS += profile.mine.txt
CLEANTARGETS += profile.orig.txt
CLEANTARGETS += $(TARGETS)
# doxygen:
CLEANTARGETS += html latex

ALL_OBJECTS += $(ANTS_OBJECTS) $(TEST_OBJECTS) $(ORIGANTS_OBJECTS)
CLEANTARGETS += $(ALL_OBJECTS)

# clean dependency files if any
CLEANTARGETS += $(subst .o,.d,$(ALL_OBJECTS))

GPROF := gprof --line --no-graph --brief

all : $(TARGETS)

antsTest.diff: ants.out
	diff -up ../ps2/ants.out.default ants.out > $@

ants.out: ants
	./ants > $@

ants : $(ANTS_OBJECTS)
	$(CXX) $(LDFLAGS) -o $@ $(ANTS_OBJECTS) $(ANTS_LDLIBS)

origants : $(ORIGANTS_OBJECTS)
	$(CXX) $(LDFLAGS) -o $@ $(ORIGANTS_OBJECTS) $(ANTS_LDLIBS)

test: testdriver
	./testdriver --report_level=detailed

testdriver : $(TEST_OBJECTS)
	$(CXX) $(LDFLAGS) -o $@ $(TEST_OBJECTS) $(TEST_LDLIBS)

.gitignore: GNUmakefile
	echo $(addprefix $(THISDIR)/,$(CLEANTARGETS)) | tr ' ' '\n' > $@

clean::
	rm -rf $(CLEANTARGETS)

profile.mine.txt: ants
	rm -f gmon.out
	./ants -t 400 > mine.out
	$(GPROF) ./ants > $@

profile.orig.txt: origants
	rm -f gmon.out
	./origants > orig.out
	$(GPROF) ./origants > $@

# read in dependency files:
-include $(wildcard *.d)
