include ../make.vars
#CXXFLAGS += -std=c++14
CXXFLAGS += -g
LDFLAGS += -lpthread
#CXXFLAGS += -O2

all : sharedptr

sharedptr : sharedptr.o
	$(CXX) -o $@ $(CXXFLAGS) $(LDFLAGS) sharedptr.o

clean:
	rm -f *.o sharedptr

include ../make.rules
