include ../make.vars

CXXFLAGS += -O2
#CXXFLAGS += -g

OBJECTS += m.o
OBJECTS += matrix.o

ifdef NO_INLINE_M2
   OBJECTS += m2.o
else
   CXXFLAGS += -DINLINE_M2
endif

m : $(OBJECTS)
	$(CXX) -o $@ $(CXXFLAGS) $(OBJECTS)

clean :
	rm -f m *.o *.d

include ../make.rules
