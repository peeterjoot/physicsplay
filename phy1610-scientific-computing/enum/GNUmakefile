#PRODUCTION := 1
#PROFILED := 1
#USE_OPENBLAS := 1

include ../make.vars

TARGETS += enum
ENUM_SOURCES += enum.cc
ENUM_SOURCES += enum1.cc
ENUM_OBJECTS := $(subst .cc,.o,$(ENUM_SOURCES))

CLEANTARGETS += $(TARGETS)

all : $(TARGETS)

enum : $(ENUM_OBJECTS)
	$(CXX) -o $@ $(ENUM_OBJECTS) $(LDFLAGS) $(ENUM_LDFLAGS) $(LDLIBS) $(ENUM_LDLIBS)

include ../make.rules
