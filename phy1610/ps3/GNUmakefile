OSNAME := $(shell uname -o)

# for windows (cygwin):
CXXFLAGS += -D_GLIBCXX_USE_C99

# generate dependency files with each compilation:
CXXFLAGS += -MMD

#CXXFLAGS += -I../inc
CXXFLAGS += -I../../rarray

TICKTOCK := $(HOME)/ticktock
CXXFLAGS += -I$(TICKTOCK)

PRODUCTION := 1
PROFILED := 1
ifdef PRODUCTION
   CXXFLAGS += -DNDEBUG
   CXXFLAGS += -O2
else
   CXXFLAGS += -g
endif
ifdef PROFILED
   CXXFLAGS += -pg -g
   LDFLAGS += -pg -g
endif

CXXFLAGS += -Wall -Werror
CXXFLAGS += -std=c++11
THISDIR := phy1610/ps3

TARGETS += .gitignore

ifeq ("$(OSNAME)","Cygwin")
   # get cxx11 abi link errors attempting to use boost unit_test with the pre-compiled boost library
   CXXFLAGS += -DUSE_SINGLE_HEADER_BOOST_TEST_FRAMEWORK

   # for putenv and mkstemp
   CXXFLAGS += -U__STRICT_ANSI__
else
   TEST_LDLIBS += -lboost_unit_test_framework
endif

#TARGETS += antsTest.diff
TARGETS += ants.cc
TARGETS += ants_on_table.cc
TARGETS += ants_on_table.h
TARGETS += ants
TARGETS += origants
#TARGETS += ants.out
ANTS_SOURCES += ants.cc
ANTS_SOURCES += ticktock.cc
ANTS_SOURCES += ants_on_table.cc
ANTS_SOURCES += $(COMMON_SOURCES)
ANTS_OBJECTS := $(subst .cc,.o,$(ANTS_SOURCES))

ORIGANTS_OBJECTS += origants.o 
ORIGANTS_OBJECTS += ticktock.o 

#TARGETS += test
#TEST_SOURCES += test.cc
#TEST_SOURCES += $(COMMON_SOURCES)
#TEST_OBJECTS := $(subst .cc,.o,$(TEST_SOURCES))

CLEANTARGETS += gmon.out
CLEANTARGETS += orig.out
CLEANTARGETS += mine.out
CLEANTARGETS += profile.mine.txt
CLEANTARGETS += profile.orig.txt
CLEANTARGETS += $(TARGETS)
# doxygen:
CLEANTARGETS += html latex

CLEANTARGETS += $(ANTS_OBJECTS) $(TEST_OBJECTS)

# clean dependency files if any
CLEANTARGETS += $(subst .o,.d,$(TEST_OBJECTS) $(ANTS_OBJECTS))

TARFILES += ants.cc
TARFILES += ticktock.cc
TARFILES += ants.out.default
TARFILES += ants.out
TARFILES += ants_on_table.cc
TARFILES += ants_on_table.h
TARFILES += git.log
TARFILES += GNUmakefile
CLEANTARGETS += git.log
CLEANTARGETS += ps2.tar

all : $(TARGETS)

antsTest.diff: ants.out
	diff -up ../ps2/ants.out.default ants.out > $@

ants.out: ants
	./ants > $@

ants : $(ANTS_OBJECTS)
	$(CXX) -o $@ $(ANTS_OBJECTS) $(ANTS_LDLIBS) $(LDFLAGS)

origants : $(ORIGANTS_OBJECTS)
	$(CXX) -o $@ $(ORIGANTS_OBJECTS) $(ANTS_LDLIBS) $(LDFLAGS)

test : $(TEST_OBJECTS)
	$(CXX) -o $@ $(TEST_OBJECTS) $(TEST_LDLIBS) $(LDFLAGS)

.gitignore: GNUmakefile
	echo $(addprefix $(THISDIR)/,$(CLEANTARGETS)) | tr ' ' '\n' > $@

git.log : 
	git log --stat . > $@

ps2.tar : $(TARFILES)
	rm -f $@
	tar cf $@ $(TARFILES)

clean::
	rm -rf $(CLEANTARGETS)

ants.cc : ../ps2/ants.cc
	cp $^ $@

ticktock.cc : $(TICKTOCK)/ticktock.cc
	cp $^ $@

ants_on_table.cc : ../ps2/ants_on_table.cc
	cp $^ $@

ants_on_table.h : ../ps2/ants_on_table.h
	cp $^ $@

profile.mine.txt: ants
	rm -f gmon.out
	./ants > mine.out
	gprof --line ./ants > $@

profile.orig.txt: origants
	rm -f gmon.out
	./origants > orig.out
	gprof --line ./origants > $@

# read in dependency files:
-include $(wildcard *.d)
