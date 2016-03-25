#
# All Programs -> VS 9 -> Vs Tools -> VS command prompt
# set PATH=%PATH%;c:\cygwin\bin
#

EXE := .EXE
OBJ := obj

#TESTINC := $(subst .h,_testinc.cpp,$(shell echo *.h))
#TESTINC_bin := $(subst .cpp,.$(OBJ),$(TESTINC))

GASAND := $(HOME)/gasand/ga_sandbox-1.0.5
#LDFLAGS_GASAND := -L$(GASAND)/lib_win32

SOURCES += expression.cpp
SOURCES += term.cpp

gasym_SOURCE += sum.cpp
gasym_SOURCE += symbol.cpp
#gasym_SOURCE += $(GASAND)/libgasandbox/e3ga.cpp
gasym_SOURCE += gasym.cpp
gasym_SOURCE += $(SOURCES)

calc_SOURCE += calc.cpp
calc_SOURCE += $(SOURCES)

#COPTS += -g
#COPTS += -O2
#CXX := g++

#COPTS += -g
#COPTS += -O2
#CXX := g++
CXX := CL /nologo

GASANDBOX := ../../gasand/ga2/ga_sandbox-1.0.7
#LIBGLUT := freeglut.lib

LIBGASANDBOX += ../../gasand/ga25/TestG25/e3ga_cpp/e3ga.obj

CXXFLAGS += /Zi -DWIN32 /EHsc
#CXXFLAGS += -I../../gasand/ga25/TestG25/e2ga_cpp
#CXXFLAGS += -I../../gasand/ga25/TestG25/c3ga_cpp
CXXFLAGS += -I../../gasand/ga25/TestG25/e3ga_cpp
#CXXFLAGS += -I.

COMPILE = $(CXX) $(CXXFLAGS) /c /Fo$*.$(OBJ)
LINK = $(CXX) /Fe$@

gasym_OBJECTS := $(subst .cpp,.$(OBJ),$(gasym_SOURCE))
calc_OBJECTS := $(subst .cpp,.$(OBJ),$(calc_SOURCE))

FILES := $(shell ls *.ltx)
PDFS := $(FILES:.ltx=.pdf)

#LATEX_HELPER_DIR := /cygdrive/d/peeterj/personal/math

all :: $(gasym_OBJECTS)
all :: gasym$(EXE)
#all :: $(calc_OBJECTS)
#all :: calc$(EXE)

#all :: $(TESTINC_bin)
#all :: trygin$(EXE)
#all :: $(PDFS)

%.$(OBJ) : %.cpp
	$(CXX) $(CXXFLAGS) $(COPTS) /c $^

#%.$(OBJ) : $(GASAND)/libgasandbox/%.cpp
#	$(CXX) $(CXXFLAGS) $(COPTS) -c $^

#LIBS_GINAC := -L $(HOME)/local/lib -lginac -lcln
#trygin$(EXE) : trygin.$(OBJ)
#	$(CXX) $(LDFLAGS_GASAND) $(CXXFLAGS) $^ $(LIBS_GINAC) /Fe$@

gasym$(EXE) : $(gasym_OBJECTS)
	$(CXX) $(LDFLAGS_GASAND) $(CXXFLAGS) $^ $(LIBGASANDBOX) /Fe$@

calc$(EXE) : $(calc_OBJECTS)
	$(CXX) $(LDFLAGS_GASAND) $(CXXFLAGS) $^ /Fe$@

%_testinc.cpp : %.h
	perl mktestinc $^

%.pdf : %.ltx
	$(LATEX_HELPER_DIR)/make_pdflatex $<

#----------------------------
# header dependencies:
#
# grep -F .h xx.yy | sed 's/:.* "//;s/".*//'
#

expression.cpp : expression.h
gasym.cpp : sum.h
sum.cpp : sum.h
symbol.cpp : symbol.h
term.cpp : term.h
expression.h : term.h
sum.h : symbol.h
symbol.h : expression.h term.h

#----------------------------
