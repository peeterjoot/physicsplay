include ../make.vars

CXXFLAGS += -O2

all : d out.dis

d : d.o out.o
	$(CXX) -o $@ $(CXXFLAGS) d.o out.o

include ../make.rules
