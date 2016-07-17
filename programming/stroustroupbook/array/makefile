include ../make.vars
#CXXFLAGS += -g
CXXFLAGS += -O2

d : d.o
	$(CXX) -o $@ $(CXXFLAGS) d.o

clean:
	rm -f *.o d

include ../make.rules
