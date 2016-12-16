include ../make.vars
CXXFLAGS += -std=c++14
#CXXFLAGS += -g
CXXFLAGS += -O2

all : u

u : u.o
	$(CXX) -o $@ $(CXXFLAGS) u.o

clean:
	rm -f *.o u

include ../make.rules
