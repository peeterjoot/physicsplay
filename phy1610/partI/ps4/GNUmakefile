OSNAME := $(shell uname -o)

# for windows (cygwin):
CXXFLAGS += -D_GLIBCXX_USE_C99

# generate dependency files with each compilation:
CXXFLAGS += -MMD
CXXFLAGS += -Wall
CXXFLAGS += -I../ps1
CXXFLAGS += -std=c++11

# PRODUCTION := 1
ifdef PRODUCTION
   CXXFLAGS += -DNDEBUG
   CXXFLAGS += -O2
else
   CXXFLAGS += -g
   CXXFLAGS += -pg -O0
   LDFLAGS += -pg -O0
endif

THISDIR := phy1610/partI/ps4

TARGETS += mm
TARGETS += test
TARGETS += .gitignore

MM_SOURCES += mm.cc mymatrix.cc mymultiply.cc ticktock.cc
MM_OBJECTS := $(subst .cc,.o,$(MM_SOURCES))

CLEANTARGETS += $(TARGETS)
# doxygen:
CLEANTARGETS += html latex

CLEANTARGETS += *.o

# clean dependency files if any
CLEANTARGETS += $(subst .cc,.d,$(wildcard *.cc))

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
	./mm > profile.txt
	@echo "ERROR: You need to implement the rest of this as part of the assignment!" >> profile.txt

clean::
	rm -rf $(CLEANTARGETS)

# read in dependency files:
-include $(wildcard *.d)
