#CXXFLAGS += -std=c++14
CXXFLAGS += -std=c++11
#CXXFLAGS += -g
CXXFLAGS += -O2
CXXFLAGS += -Wall

all : d b

d : d.o
	$(CXX) -o $@ $(CXXFLAGS) d.o

b : b.o
	$(CXX) -o $@ $(CXXFLAGS) b.o

%.dis : %.o
	gobjdump -d --reloc -C --no-show-raw-insn $< > $@

clean:
	rm -f *.o d b
