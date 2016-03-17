# Makefile for diffring and walkring
#
# Ramses van Zon, March 2016
#

SCINET_OPENBLAS_INC?=.
SCINET_OPENBLAS_LIB?=.

CXX=g++
CXXFLAGS=-O3 -g -std=c++11 -I${SCINET_OPENBLAS_INC}
LDFLAGS=-g -L${SCINET_OPENBLAS_LIB}
LDLIBS=-lopenblas
LD=${CXX}

.PHONY: all clean run rundiffring runwalkring

all: diffring walkring

diffring: diffring.o diffring_timestep.o diffring_output.o diffring_parameters.o ticktock.o sparkline.o
	${LD} ${LDFLAGS} -o diffring diffring.o diffring_timestep.o diffring_output.o diffring_parameters.o ticktock.o sparkline.o ${LDLIBS}

walkring: walkring.o ticktock.o sparkline.o walkring_output.o walkring_timestep.o walkring_parameters.o
	${LD} ${LDFLAGS} -o walkring walkring.o ticktock.o sparkline.o walkring_output.o walkring_timestep.o walkring_parameters.o ${LDLIBS}

diffring.o: diffring.cc diffring_timestep.h
	${CXX} ${CXXFLAGS} -c -o diffring.o diffring.cc

walkring.o: walkring.cc walkring_output.h walkring_timestep.h walkring_parameters.h
	${CXX} ${CXXFLAGS} -c -o walkring.o walkring.cc

walkring_output.o: walkring_output.cc walkring_output.h
	${CXX} ${CXXFLAGS} -c -o walkring_output.o walkring_output.cc

walkring_timestep.o: walkring_timestep.cc walkring_timestep.h
	${CXX} ${CXXFLAGS} -c -o walkring_timestep.o walkring_timestep.cc

walkring_parameters.o: walkring_parameters.cc walkring_parameters.h
	${CXX} ${CXXFLAGS} -c -o walkring_parameters.o walkring_parameters.cc

diffring_output.o: diffring_output.cc diffring_output.h
	${CXX} ${CXXFLAGS} -c -o diffring_output.o diffring_output.cc

diffring_timestep.o: diffring_timestep.cc diffring_timestep.h
	${CXX} ${CXXFLAGS} -c -o diffring_timestep.o diffring_timestep.cc

diffring_parameters.o: diffring_parameters.cc diffring_parameters.h
	${CXX} ${CXXFLAGS} -c -o diffring_parameters.o diffring_parameters.cc

ticktock.o: ticktock.cc ticktock.h sparkline.h
	${CXX} ${CXXFLAGS} -c -o ticktock.o ticktock.cc

sparkline.o: sparkline.cc sparkline.h sparkline.h
	${CXX} ${CXXFLAGS} -c -o sparkline.o sparkline.cc

clean:
	\rm -rf ticktock.o diffring.o walkring.o walkring_output.o walkring_timestep.o walkring_parameters.o diffring.o diffring_output.o diffring_timestep.o diffring_parameters.o sparkline.o

run: rundiffring runwalkring

rundiffring: diffring diffring.ini
	./diffring diffring.ini

runwalkring: walkring walkring.ini
	./walkring walkring.ini

