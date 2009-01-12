exe := .exe

TESTINC := $(subst .h,_testinc.cpp,$(shell echo *.h))
testinc_bin := $(subst .cpp,.o,$(TESTINC))

source += expression.cpp
source += term.cpp

gasym_source += sum.cpp
gasym_source += symbol.cpp
gasym_source += ../libgasandbox/e3ga.cpp
gasym_source += gasym.cpp
gasym_source += $(source)

calc_source += calc.cpp
calc_source += $(source)

COPTS += -g
#COPTS += -O2

gasym_objects := $(subst .cpp,.o,$(gasym_source))
calc_objects := $(subst .cpp,.o,$(calc_source))
lobjects := $(notdir $(gasym_objects) $(calc_objects))

files := $(shell ls *.ltx)
pdfs := $(files:.ltx=.pdf)

latexrules := ./latex

all :: $(testinc_bin)
all :: $(lobjects) gasym$(exe) calc$(exe)
all :: $(pdfs)

%.o : %.cpp
	g++ -I.. -I../ext_include -I ../libgasandbox $(COPTS) -c $^

%.o : ../libgasandbox/%.cpp
	g++ -I.. -I../ext_include -I ../libgasandbox $(COPTS) -c $^

gasym$(exe) : $(notdir $(gasym_objects))
	g++ -L../lib_win32 -I.. -I../ext_include $^ $(libs) -o $@

calc$(exe) : $(calc_objects)
	g++ -L../lib_win32 -I.. -I../ext_include $^ $(libs) -o $@

%_testinc.cpp : %.h
	perl mktestinc $^

%.pdf : %.ltx
	$(latexrules)/make_pdflatex $<

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
symbol.h : expression.h

#----------------------------
