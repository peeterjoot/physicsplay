EXE := .exe
#LATEX_HELPER_DIR := /cygdrive/d/peeterj/personal/math
GASAND := $(HOME)/gasand/ga_sandbox-1.0.5
LDFLAGS += -L$(GASAND)/lib_win32
LIBRARIES += $(GASAND)/vs2005/glut32.dll
#LIBRARIES += -lglut32

COPTS += -g
#COPTS += -O2
CXX := g++

#SOURCE += julia.cpp
SOURCE += $(GASAND)/chap7/ex1/chap7ex1.cpp
SOURCE += $(GASAND)/libgasandbox/e3ga.cpp

OBJECTS := $(subst .cpp,.o,$(SOURCE))
LOCAL_OBJECTS := $(notdir $(OBJECTS))

# from ga_sandbox
CXXFLAGS += -I$(GASAND)
CXXFLAGS += -I$(GASAND)/ext_include
CXXFLAGS += -I $(GASAND)/libgasandbox

#CXXFLAGS += -I $(HOME)/local/include

#LATEX_FILES := $(shell ls *.ltx)
#PDFS := $(LATEX_FILES:.ltx=.pdf)

#-------------------------------------------

all :: $(LOCAL_OBJECTS)
all :: julia$(EXE)
#all :: $(PDFS)

%.o : %.cpp
	$(CXX) $(CXXFLAGS) $(COPTS) -c $^

# these two rules are dumb.  got to be a better way:
%.o : $(GASAND)/libgasandbox/%.cpp
	$(CXX) $(CXXFLAGS) $(COPTS) -c $^

%.o : $(GASAND)/chap7/ex1/%.cpp
	$(CXX) $(CXXFLAGS) $(COPTS) -c $^

julia$(EXE) : $(notdir $(LOCAL_OBJECTS))
	$(CXX) $(LDFLAGS) $(CXXFLAGS) $^ $(LIBRARIES) -o $@

#%.pdf : %.ltx
#	$(LATEX_HELPER_DIR)/make_pdflatex $<

#----------------------------
# header dependencies:
#
# grep -F .h xx.yy | sed 's/:.* "//;s/".*//'
#

#----------------------------
