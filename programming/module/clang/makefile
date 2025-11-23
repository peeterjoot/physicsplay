CXX := clang++
CXXFLAGS += -std=c++23
CXXFLAGS += -stdlib=libc++
CXXFLAGS += -Wall -Wextra
CXXFLAGS += -Werror

STD_MODULE := -fmodule-file=std=std.pcm
STDCXX     := /usr/share/libc++/v1/std.cppm

MODULES += std.pcm
MODULES += stuff.pcm

PCMFLAGS_std += -Wno-reserved-module-identifier
PCMFLAGS_stuff += $(STD_MODULE)

CXXFLAGS_try += -fmodule-file=stuff=stuff.pcm

VPATH := /usr/share/libc++/v1

all: try

%.o: %.cc            # ← this cancels the built-in rule
#%: %.o               # optional, also kills the built-in link rule if you want

%.pcm: %.cppm
	$(CXX) $(CXXFLAGS) $(PCMFLAGS_$*) --precompile $< -o $@

%.o: %.cc | $(MODULES)
	$(CXX) $(CXXFLAGS) $(STD_MODULE) $(CXXFLAGS_$*) -c $< -o $@

try: try.o stuff.o
	$(CXX) $(CXXFLAGS) $(STD_MODULE) -fmodule-file=stuff=stuff.pcm try.o stuff.o -o $@

clean:
	rm -f *.o *.pcm try

.PHONY: all clean
