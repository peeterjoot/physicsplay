# Makefile for example matrix multiplying code mm.cc, using matrix
# implemented in mymatrix.cc/mymatrix.h
#
# Part of HW 4 of 'scientific computing - software development'. 
#
# Ramses van Zon, January 2015
#
CXX=g++
LDFLAGS=-g -pg -O0
CXXFLAGS=-g -pg -O0 -Wall
OBJS=mm.o mymatrix.o mymultiply.o ticktock.o

all: mm

profile: profile.txt
	@cat profile.txt

mm: ${OBJS}
	${CXX} ${LDFLAGS} ${OBJS} -o mm

mm.o: mm.cc mymatrix.h mymultiply.h ticktock.h
	${CXX} ${CXXFLAGS} -c -o mm.o mm.cc

mymatrix.o: mymatrix.cc mymatrix.h
	${CXX} ${CXXFLAGS} -c -o mymatrix.o mymatrix.cc

mymultiply.o: mymultiply.cc mymultiply.h mymatrix.h
	${CXX} ${CXXFLAGS} -c -o mymultiply.o mymultiply.cc

ticktock.o: ticktock.cc ticktock.h
	${CXX} ${CXXFLAGS} -c -o ticktock.o ticktock.cc

clean:
	\rm -f  ${OBJS}

profile.txt: mm
	./mm > profile.txt
	@echo "ERROR: You need to implement the rest of this as part of the assignment!" >> profile.txt

