CXXSTANDARD ?= c++17
include ../stroustroupbook/make.vars
CXXFLAGS += -g

# MacOS:
#CXXFLAGS += -I/usr/local/Cellar/eigen/3.3.7/include/eigen3
# ubuntu:
CXXFLAGS += -I/usr/include/eigen3

CXXFLAGS += -Wno-error=unused-variable
#CXXFLAGS += -O2
LDFLAGS_E2GA += -le2ga
LDFLAGS_E3GA += -le3ga

TARGETS += e2ga
TARGETS += e3ga
#TARGETS += issue4
#TARGETS += issue7

all : $(TARGETS)

e2ga : e2ga.o
	$(CXX) -o $@ $(CXXFLAGS) e2ga.o $(LDFLAGS_E2GA)

e3ga : e3ga.o
	$(CXX) -o $@ $(CXXFLAGS) e3ga.o $(LDFLAGS_E3GA)

issue4 : issue4.o
	$(CXX) -o $@ $(CXXFLAGS) issue4.o $(LDFLAGS_E3GA)

issue7 : issue7.o
	$(CXX) -o $@ $(CXXFLAGS) issue7.o $(LDFLAGS_E3GA)

clean:
	rm -f *.o *.d *.i $(TARGETS)

include ../stroustroupbook/make.rules
