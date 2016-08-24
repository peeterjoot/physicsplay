#PRODUCTION := 1
#PROFILED := 1
#USE_OPENBLAS := 1

include ../make.vars

TARFILES += ants.cc
TARFILES += ants.out.default
TARFILES += ants.out
TARFILES += ants_on_table.cc
TARFILES += ants_on_table.h
TARFILES += git.log
TARFILES += GNUmakefile

TARGETS += antsTest.diff
TARGETS += ants
TARGETS += ants.out
ANTS_SOURCES += ants.cc
ANTS_SOURCES += ants_on_table.cc
ANTS_SOURCES += $(COMMON_SOURCES)
ANTS_OBJECTS := $(subst .cc,.o,$(ANTS_SOURCES))

CLEANTARGETS += $(ANTS_OBJECTS) $(TEST_OBJECTS)
CLEANTARGETS += $(TARGETS)

all : $(TARGETS)

antsTest.diff: ants.out
	diff -up ants.out.default ants.out > $@

ants.out: ants
	./ants > $@

ants : $(ANTS_OBJECTS)
	$(CXX) -o $@ $(ANTS_OBJECTS) $(ANTS_LDLIBS)

test : $(TEST_OBJECTS)
	$(CXX) -o $@ $(TEST_OBJECTS) $(TEST_LDLIBS)

ps2.tar : $(TARFILES)
	rm -f $@
	tar cf $@ $(TARFILES)

include ../make.rules
