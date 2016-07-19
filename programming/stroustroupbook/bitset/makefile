include ../make.vars
#CXXFLAGS += -std=c++14
#CXXFLAGS += -g
CXXFLAGS += -O2

all : d b

d : d.o
	$(CXX) -o $@ $(CXXFLAGS) d.o

b : b.o
	$(CXX) -o $@ $(CXXFLAGS) b.o

clean:
	rm -f *.o d b

include ../make.rules
