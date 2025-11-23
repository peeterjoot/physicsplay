CXX := clang++
CXXFLAGS += -std=c++23 -stdlib=libc++ -Wall -Wextra

# Disable Make's hard-coded built-in module rules (they ignore .SUFFIXES:)
%pcm: %cc   # ← THIS LINE IS THE KEY

STD_MODULE := -fmodule-file=std=std.pcm
STDCXX     := /usr/share/libc++/v1/std.cppm

all: try

std.pcm: $(STDCXX)
	$(CXX) $(CXXFLAGS) -Wno-reserved-module-identifier --precompile $< -o $@

stuff.pcm: stuff.cppm std.pcm
	$(CXX) $(CXXFLAGS) $(STD_MODULE) --precompile $< -o $@

try.o : %.o: %.cc stuff.pcm std.pcm
	$(CXX) $(CXXFLAGS) $(STD_MODULE) -fmodule-file=stuff=stuff.pcm -c $< -o $@

stuff.o : %.o: %.cc stuff.pcm std.pcm
	$(CXX) $(CXXFLAGS) $(STD_MODULE) -c $< -o $@

try: try.o stuff.o
	$(CXX) $(CXXFLAGS) $(STD_MODULE) -fmodule-file=stuff=stuff.pcm try.o stuff.o -o $@

clean:
	rm -f *.o *.pcm try

.PHONY: all clean
