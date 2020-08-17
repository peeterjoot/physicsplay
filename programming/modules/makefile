CXX := /opt/lzlabs/lldb/bin/clang++
CC := $(CXX)
CXXFLAGS += -g
CXXFLAGS += -Wall
CXXFLAGS += -MMD

TARGET := main

all : $(TARGET)

main: main.o matrix.o

clean:
	rm -f *.o $(TARGET) *.d

-include *.d
