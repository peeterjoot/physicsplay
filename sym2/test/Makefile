#EXE := .exe
COPTS += -g
#COPTS += -O2
CXX := g++
CXXFLAGS += -I $(HOME)/local/include
LIBS_GINAC := -L $(HOME)/local/lib -lginac -lcln

all :: trygin$(EXE)

%.o : %.cpp
	$(CXX) $(CXXFLAGS) $(COPTS) -c $^

trygin$(EXE) : trygin.o
	$(CXX) $(LDFLAGS_GASAND) $(CXXFLAGS) $^ $(LIBS_GINAC) -o $@

#----------------------------
# header dependencies:
#
# grep -F .h xx.yy | sed 's/:.* "//;s/".*//'
#

#----------------------------
