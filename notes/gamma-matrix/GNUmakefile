#EXE := .exe

SOURCE := matrix.cpp

COPTS += -g
#COPTS += -I$(HOME)/boostlib/include/boost-1_37/
#COPTS += -O2

OBJECTS := $(subst .cpp,.o,$(SOURCE))

all :: $(OBJECTS) matrix$(EXE) .gitignore

.gitignore : GNUmakefile
	rm -f .gitignore
	touch $@

%.o : %.cpp
	g++ $(COPTS) -c $^

matrix$(EXE) : $(OBJECTS)
	g++ $(OBJECTS) -o $@
