EXE := .exe
OBJ := o

OBJECTS := del2xml.$(OBJ)
CFLAGS := -Wformat
CFLAGS += -g
CXXFLAGS := $(CFLAGS)

all : del2xml$(EXE) build.bat

del2xml$(EXE) : $(OBJECTS)
	g++ $(CFLAGS) -o $@ $(OBJECTS)

del2xml.$(OBJ) : commit.h

commit.h: Makefile del2xml.cpp
	echo 'char commitString[] = "'`~/bin/mkRevInfo -commit`'" ;' > $@

clean:
	rm -f del2xml$(EXE) *.obj *.o *.xml commit.h

build.bat : Makefile commit.h
	rm -f build.bat
	echo cl -c ../getopt/getopt.c -I../getopt > build.bat
	echo cl -c ../getopt/getopt1.c -I../getopt >> build.bat
	echo cl -Fedel2xml.exe /EHsc del2xml.cpp getopt.obj getopt1.obj -I../getopt >> build.bat
