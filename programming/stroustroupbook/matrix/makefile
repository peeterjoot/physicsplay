CXXFLAGS += -std=c++11
CXXFLAGS += -O2
CXXFLAGS += -MMD
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

-include $(wildcard *.d)

clean :
	rm -f m *.o *.d
