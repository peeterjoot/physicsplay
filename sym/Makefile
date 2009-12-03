exe := .exe

#TESTINC := $(subst .h,_testinc.cpp,$(shell echo *.h))
#testinc_bin := $(subst .cpp,.o,$(TESTINC))

GASAND := $(HOME)/gasand/ga_sandbox-1.0.5
LDFLAGS_GASAND := -L$(GASAND)/lib_win32

source += expression.cpp
source += term.cpp

gasym_source += sum.cpp
gasym_source += symbol.cpp
gasym_source += $(GASAND)/libgasandbox/e3ga.cpp
gasym_source += gasym.cpp
gasym_source += $(source)

calc_source += calc.cpp
calc_source += $(source)

COPTS += -g
#COPTS += -O2

CXX := g++

gasym_objects := $(subst .cpp,.o,$(gasym_source))
calc_objects := $(subst .cpp,.o,$(calc_source))
lobjects := $(notdir $(gasym_objects) $(calc_objects))

files := $(shell ls *.ltx)
pdfs := $(files:.ltx=.pdf)

LATEX_HELPER_DIR := /cygdrive/d/peeterj/personal/math

#all :: $(testinc_bin)
all :: $(lobjects)
#all :: trygin$(exe)
all :: gasym$(exe)
all :: calc$(exe)
#all :: $(pdfs)

# from ga_sandbox
CXXFLAGS += -I$(GASAND)
CXXFLAGS += -I$(GASAND)/ext_include
CXXFLAGS += -I $(GASAND)/libgasandbox

#CXXFLAGS += -I $(HOME)/local/include

%.o : %.cpp
	$(CXX) $(CXXFLAGS) $(COPTS) -c $^

%.o : $(GASAND)/libgasandbox/%.cpp
	$(CXX) $(CXXFLAGS) $(COPTS) -c $^

#LIBS_GINAC := -L $(HOME)/local/lib -lginac -lcln

#trygin$(exe) : trygin.o
#	$(CXX) $(LDFLAGS_GASAND) $(CXXFLAGS) $^ $(LIBS_GINAC) -o $@

gasym$(exe) : $(notdir $(gasym_objects))
	$(CXX) $(LDFLAGS_GASAND) $(CXXFLAGS) $^ $(libs) -o $@

calc$(exe) : $(calc_objects)
	$(CXX) $(LDFLAGS_GASAND) $(CXXFLAGS) $^ $(libs) -o $@

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
