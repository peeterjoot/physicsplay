CXXFLAGS += -std=c++11
THISDIR := phy1610/partI/ps2

# toggle these for debug vs. optimize
CXXFLAGS += -g
#CXXFLAGS += -DNDEBUG
#CXXFLAGS += -O2

TARGETS += wave1d
TARGETS += .gitignore
#TARGETS += waveparams.txt

all: $(TARGETS)

CLEANTARGETS += $(TARGETS)
# doxygen:
CLEANTARGETS += html latex

.gitignore: GNUmakefile
	echo $(addprefix $(THISDIR)/,$(CLEANTARGETS)) | tr ' ' '\n' > $@

clean::
	rm -rf $(CLEANTARGETS)

#base:
#	wget https://support.scinet.utoronto.ca/education/get.php/wave1d.cc
#
#waveparams.txt:
#	wget https://support.scinet.utoronto.ca/education/get.php/waveparams.txt
