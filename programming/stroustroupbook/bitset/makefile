#CXXFLAGS += -std=c++14
CXXFLAGS += -std=c++11
#CXXFLAGS += -g
CXXFLAGS += -O2
CXXFLAGS += -Wall

d : d.o
	$(CXX) -o $@ $(CXXFLAGS) d.o

%.dis : %.o
	gobjdump -d --reloc -C --no-show-raw-insn $< > $@

clean:
	rm -f *.o d
