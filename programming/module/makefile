CXXFLAGS += -std=c++23
CXXFLAGS += -fmodules

# This assumes g++ is g++-15
STDCXX := /usr/include/c++/15/bits/std.cc

all : try

try: std.o try.o
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS) $(LOADLIBES)

std.o : $(STDCXX)
	$(CXX) $(CXXFLAGS) -c $(STDCXX)

clean:
	rm -rf *.o try gcm.cache
