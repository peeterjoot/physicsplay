CXXFLAGS += -std=c++11
CXXFLAGS += -O2
CXXFLAGS += -MMD

d : d.o out.o
	$(CXX) -o $@ $(CXXFLAGS) d.o out.o

-include $(wildcard *.d)
