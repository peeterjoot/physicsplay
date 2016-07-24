include ../make.vars
#CXXFLAGS += -std=c++14
CXXFLAGS += -g
CXXFLAGS += -Wno-unknown-escape-sequence
#LDFLAGS += -lpthread
#CXXFLAGS += -O2

TARGETS += rp

all : $(TARGETS)

rp : rp.o
	$(CXX) -o $@ $(CXXFLAGS) $(LDFLAGS) rp.o

clean:
	rm -f *.o $(TARGETS)

include ../make.rules
