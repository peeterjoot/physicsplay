CXXFLAGS += -g
CXXFLAGS += -std=c++11
#LDFLAGS += -lboost_regex
#HOSTNAME := $(shell hostname)

#include makefile.$(HOSTNAME)

EXES += regexMatch

all: $(EXES)

%.o : %.cpp
	$(CXX) -c $< $(CFLAGS)

regexMatch: regexMatch.o
	$(CXX) $< -o $@ $(LDFLAGS)

clean:
	rm -rf *.o $(EXES)
