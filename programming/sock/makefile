include ../stroustroupbook/make.vars
CXXFLAGS += -std=c++11
CXXFLAGS += -g
#CXXFLAGS += -O2

TARGETS += server
TARGETS += client
TARGETS += dump

all :: $(TARGETS)

server : server.o
	$(CXX) -o $@ $(CXXFLAGS) $^

dump : dump.o
	$(CXX) -o $@ $(CXXFLAGS) $^

client : client.o
	$(CXX) -o $@ $(CXXFLAGS) $^

clean:
	rm -f *.o *.d server $(TARGETS)

include ../stroustroupbook/make.rules
