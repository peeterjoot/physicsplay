include ../make.vars
#CXXFLAGS += -std=c++14
CXXFLAGS += -g
CXXFLAGS += -Wno-unknown-escape-sequence
#LDFLAGS += -lpthread
#CXXFLAGS += -O2

TARGETS += rp
TARGETS += rs

all : $(TARGETS)

rp : rp.o
	$(CXX) -o $@ $(CXXFLAGS) $(LDFLAGS) rp.o

rs : rs.o
	$(CXX) -o $@ $(CXXFLAGS) $(LDFLAGS) rs.o

clean:
	rm -f *.o $(TARGETS)

include ../make.rules
