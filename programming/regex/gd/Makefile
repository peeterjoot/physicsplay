exe := .exe

CXX := g++
COPTS += -g

#BOOST := $(HOME)/boostlib
#COPTS += -I$(BOOST)/include/boost-1_37/
#LDFLAGS += -L$(BOOST)/lib
#LOADLIBES += $(BOOST)/lib/boost_regex-gcc34-mt-1_37.so

COPTS += -I/usr/include/boost-1_33_1
LOADLIBES += -lboost_regex-gcc-mt

all :: r2$(exe)
//all :: r$(exe)

%.o : %.cpp
	$(CXX) $(CXXFLAGS) $(COPTS) -c $^

r2$(exe) : r2.o
	$(CXX) $(LDFLAGS) $(CXXFLAGS) $^ $(LOADLIBES) -o $@

r$(exe) : r.o
	$(CXX) $(LDFLAGS) $(CXXFLAGS) $^ $(LOADLIBES) -o $@

#----------------------------
# header dependencies:
#
# grep -F .h xx.yy | sed 's/:.* "//;s/".*//'
#

#----------------------------
