OSNAME := $(shell uname -o)

# for windows (cygwin):
CXXFLAGS += -D_GLIBCXX_USE_C99

# generate dependency files with each compilation:
CXXFLAGS += -MMD

CXXFLAGS += -I../inc
CXXFLAGS += -I$(HOME)/rarray
CXXFLAGS += -I$(SCINET_RARRAY_INC)

# PRODUCTION := 1
ifdef PRODUCTION
   CXXFLAGS += -DNDEBUG
   CXXFLAGS += -O2
else
   CXXFLAGS += -g
endif

CXXFLAGS += -Wall -Werror
CXXFLAGS += -std=c++11
THISDIR := phy1610/ps2

TARGETS += .gitignore

ifeq ("$(OSNAME)","Cygwin")
   # get cxx11 abi link errors attempting to use boost unit_test with the pre-compiled boost library
   CXXFLAGS += -DUSE_SINGLE_HEADER_BOOST_TEST_FRAMEWORK

   # for putenv and mkstemp
   CXXFLAGS += -U__STRICT_ANSI__
else
   TEST_LDLIBS += -lboost_unit_test_framework
endif

TARGETS += antsTest.diff
TARGETS += ants
TARGETS += ants.out
ANTS_SOURCES += ants.cc
ANTS_SOURCES += ants_on_table.cc
ANTS_SOURCES += $(COMMON_SOURCES)
ANTS_OBJECTS := $(subst .cc,.o,$(ANTS_SOURCES))

#TARGETS += test
#TEST_SOURCES += test.cc
#TEST_SOURCES += $(COMMON_SOURCES)
#TEST_OBJECTS := $(subst .cc,.o,$(TEST_SOURCES))

CLEANTARGETS += $(TARGETS)
# doxygen:
CLEANTARGETS += html latex

CLEANTARGETS += $(ANTS_OBJECTS) $(TEST_OBJECTS)

# clean dependency files if any
CLEANTARGETS += $(subst .o,.d,$(TEST_OBJECTS) $(ANTS_OBJECTS))

TARFILES += ants.cc
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
	diff -up ants.out.default ants.out > $@

ants.out: ants
	./ants > $@

ants : $(ANTS_OBJECTS)
	$(CXX) -o $@ $(ANTS_OBJECTS) $(ANTS_LDLIBS)

test : $(TEST_OBJECTS)
	$(CXX) -o $@ $(TEST_OBJECTS) $(TEST_LDLIBS)

.gitignore: GNUmakefile
	echo $(addprefix $(THISDIR)/,$(CLEANTARGETS)) | tr ' ' '\n' > $@

git.log : 
	git log --stat . > $@

ps2.tar : $(TARFILES)
	rm -f $@
	tar cf $@ $(TARFILES)

clean::
	rm -rf $(CLEANTARGETS)

# read in dependency files:
-include $(wildcard *.d)
