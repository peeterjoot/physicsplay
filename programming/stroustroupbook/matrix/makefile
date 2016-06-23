CXXFLAGS += -std=c++11
CXXFLAGS += -O2
CXXFLAGS += -MMD
#CXXFLAGS += -g

OBJECTS += m.o
ifdef INLINE_M2
   CXXFLAGS += -DINLINE_M2
else
   OBJECTS += m2.o
endif

m : $(OBJECTS)
	$(CXX) -o $@ $(CXXFLAGS) $(OBJECTS)

-include $(wildcard *.d)

clean :
	rm -f m *.o *.d
