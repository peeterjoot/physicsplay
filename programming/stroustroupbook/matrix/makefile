CXXFLAGS += -std=c++11
CXXFLAGS += -O2
#CXXFLAGS += -g

m : m.o m2.o
	$(CXX) -o $@ $(CXXFLAGS) m.o m2.o

m.o : matrix.h
m2.o : matrix.h

clean :
	rm -f m m.o m2.o
