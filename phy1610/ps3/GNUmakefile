OSNAME := $(shell uname -o)

#CXXFLAGS += -DUSE_TICK_TOCK

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
   CXXFLAGS += -D_GLIBCXX_USE_C99

   # get cxx11 abi link errors attempting to use boost unit_test with the pre-compiled boost library
   CXXFLAGS += -DUSE_SINGLE_HEADER_BOOST_TEST_FRAMEWORK

   # for putenv and mkstemp
   CXXFLAGS += -U__STRICT_ANSI__
else
   TEST_LDLIBS += -lboost_unit_test_framework
endif

#TARGETS += antsTest.diff
TARGETS += ticktock.cc
TARGETS += ants_on_table.h
TARGETS += ants.cc
TARGETS += ants_on_table.cc
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

ALL_OBJECTS += $(ANTS_OBJECTS) $(TEST_OBJECTS) $(ORIGANTS_OBJECTS)
CLEANTARGETS += $(ALL_OBJECTS)

# clean dependency files if any
CLEANTARGETS += $(subst .o,.d,$(ALL_OBJECTS))

TARFILES += ants.cc
TARFILES += ticktock.cc
TARFILES += ants.out.default
TARFILES += ants.out
TARFILES += ants_on_table.cc
TARFILES += ants_on_table.h
TARFILES += git.log
TARFILES += GNUmakefile
TARFILES += runreport.txt
CLEANTARGETS += git.log
CLEANTARGETS += ps3.tar

GPROF := gprof --line --no-graph --brief

all : $(TARGETS)

ants_on_table.cc : ants_on_table.h

ants.cc : ants_on_table.h

antsTest.diff: ants.out
	diff -up ../ps2/ants.out.default ants.out > $@

ants.out: ants
	./ants > $@

ants : $(ANTS_OBJECTS)
	$(CXX) $(LDFLAGS) -o $@ $(ANTS_OBJECTS) $(ANTS_LDLIBS)

origants : $(ORIGANTS_OBJECTS)
	$(CXX) $(LDFLAGS) -o $@ $(ORIGANTS_OBJECTS) $(ANTS_LDLIBS)

test : $(TEST_OBJECTS)
	$(CXX) $(LDFLAGS) -o $@ $(TEST_OBJECTS) $(TEST_LDLIBS)

.gitignore: GNUmakefile
	echo $(addprefix $(THISDIR)/,$(CLEANTARGETS)) | tr ' ' '\n' > $@

git.log : 
	git log --stat . > $@

ps3.tar : clean $(TARFILES)
	rm -f $@
	tar cf $@ $(TARFILES)

clean::
	rm -rf $(CLEANTARGETS)

ants.cc : ../ps2/ants.cc
	cp ../ps2/ants.cc $@

ticktock.cc : $(TICKTOCK)/ticktock.cc
	cp $^ $@

$(TICKTOCK) : 
	(cd ; git clone https://github.com/vanzonr/ticktock.git)

ants_on_table.cc : ../ps2/ants_on_table.cc
	cp ../ps2/ants_on_table.cc $@

ants_on_table.h : ../ps2/ants_on_table.h
	cp $^ $@

profile.mine.txt: ants
	rm -f gmon.out
	./ants > mine.out
	$(GPROF) ./ants > $@

profile.orig.txt: origants
	rm -f gmon.out
	./origants > orig.out
	$(GPROF) ./origants > $@

# read in dependency files:
-include $(wildcard *.d)
