CXXFLAGS += -std=c++11
CXXFLAGS += -O2
CXXFLAGS += -MMD

all : d out.dis

d : d.o out.o
	$(CXX) -o $@ $(CXXFLAGS) d.o out.o

-include $(wildcard *.d)

%.dis : %.o
	gobjdump -d --reloc -C --no-show-raw-insn $< > $@
