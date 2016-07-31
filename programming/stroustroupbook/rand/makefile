include ../make.vars

CXX := g++
CXXFLAGS += -std=c++14
CXXFLAGS += -g
#LDFLAGS += -lpthread
#CXXFLAGS += -O2

TARGETS += r
#TARGETS += r2

all : $(TARGETS)

r : r.o
	$(CXX) -o $@ $(CXXFLAGS) $(LDFLAGS) r.o

r2 : r2.o
	$(CXX) -o $@ $(CXXFLAGS) $(LDFLAGS) r2.o

clean:
	rm -f *.o $(TARGETS)

include ../make.rules
