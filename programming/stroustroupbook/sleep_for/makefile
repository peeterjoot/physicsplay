CC := g++
CXX := g++
CXXFLAGS += -std=c++17
CXXFLAGS += -g

all : sleep

clean :
	rm -f *.o sleep
	rm -rf *.dSYM

debug : sleep
	lldb ./sleep -- 1000 
