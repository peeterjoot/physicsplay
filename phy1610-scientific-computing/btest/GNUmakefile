#PRODUCTION := 1
#PROFILED := 1

include ../make.vars
include ../make.vars.boosttest

TARGETS += test
TEST_SOURCES += test.cc
TEST_OBJECTS := $(subst .cc,.o,$(TEST_SOURCES))
TEST_LDFLAGS += $(LDFLAGS_BOOSTTEST)
TEST_LDLIBS += $(LDLIBS_BOOSTTEST)

CLEANTARGETS += $(TARGETS)

all: $(TARGETS)

test : $(TEST_OBJECTS)
	$(CXX) -o $@ $(TEST_OBJECTS) $(LDFLAGS) $(TEST_LDFLAGS) $(LDLIBS) $(TEST_LDLIBS)

CLEANTARGETS += $(TARGETS)

all : $(TARGETS)

runtest: test
	./test --report_level=detailed --log_level=all

include ../make.rules
