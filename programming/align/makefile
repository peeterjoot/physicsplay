CXXFLAGS += -std=c++11
CXXFLAGS += -O2
CXXFLAGS += -fno-omit-frame-pointer
CC := $(CXX)

all : align

clean :
	rm -f *.o align

align : foo.o align.o

foo.cc : p.pl
	./p.pl > $@
