OSNAME := $(shell uname -o)

# for windows (cygwin):
CXXFLAGS += -D_GLIBCXX_USE_C99

#CXXFLAGS += -DWITH_ARRAY

# 16X slower with range checking (and associated function calls).
#CXXFLAGS += -DMYMATRIX_DO_RANGE_CHECKING

# generate dependency files with each compilation:
CXXFLAGS += -MMD
CXXFLAGS += -Wall -Werror
CXXFLAGS += -I../../inc
CXXFLAGS += -I../ps3
CXXFLAGS += -std=c++11

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

THISDIR := phy1610/2015/ps4

TARGETS += profile.txt
TARGETS += mm
#TARGETS += test
TARGETS += .gitignore

MM_SOURCES += mm.cc ../ps3/MyMatrix.cc mymultiply.cc ticktock.cc
MM_OBJECTS := $(subst .cc,.o,$(MM_SOURCES))

CLEANTARGETS += $(TARGETS)
# doxygen:
CLEANTARGETS += html latex

CLEANTARGETS += $(MM_OBJECTS)
CLEANTARGETS += profile.txt
CLEANTARGETS += *.dat

# clean dependency files if any
CLEANTARGETS += $(subst .o,.d,$(filter %.o,$(CLEANTARGETS)))

all : $(TARGETS)

mm : $(MM_OBJECTS)
	$(CXX) -o $@ $(MM_OBJECTS) $(LDFLAGS)

profile: profile.txt
	@cat profile.txt

#test : $(TEST_OBJECTS)
#	$(CXX) -o $@ $(TEST_OBJECTS) $(LDFLAGS) -lboost_unit_test_framework

.gitignore: GNUmakefile
	echo $(addprefix $(THISDIR)/,$(CLEANTARGETS)) | tr ' ' '\n' > $@

profile.txt: mm
	./mm > $@
	gprof --line ./mm >> $@

clean::
	rm -rf $(CLEANTARGETS)

# read in dependency files:
-include $(wildcard *.d)
