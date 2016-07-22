include ../make.vars
#CXXFLAGS += -std=c++14
#CXXFLAGS += -g
CXXFLAGS += -O2

all : sharedptr

sharedptr : sharedptr.o
	$(CXX) -o $@ $(CXXFLAGS) sharedptr.o

clean:
	rm -f *.o sharedptr

include ../make.rules
