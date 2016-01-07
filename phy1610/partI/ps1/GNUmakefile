CXXFLAGS += -std=c++11
THISDIR := phy1610/partI/ps1

# toggle these for debug vs. optimize
CXXFLAGS += -g
#CXXFLAGS += -DNDEBUG
#CXXFLAGS += -O2

TARGETS += tanhTable
TARGETS += .gitignore

all: $(TARGETS)

CLEANTARGETS += $(TARGETS)
# doxygen:
CLEANTARGETS += html latex

.gitignore: GNUmakefile
	echo $(addprefix $(THISDIR)/,$(CLEANTARGETS)) | tr ' ' '\n' > $@

clean::
	rm -rf $(CLEANTARGETS)
