exe := .exe

TESTINC := $(subst .h,_testinc.cpp,$(shell echo *.h))
testinc_bin := $(subst .cpp,.o,$(TESTINC))

source := ../libgasandbox/e3ga.cpp
source += expression.cpp
source += gasym.cpp
source += sum.cpp
source += symbol.cpp
source += term.cpp

COPTS += -g
#COPTS += -O2

objects := $(subst .cpp,.o,$(source))
lobjects := $(notdir $(objects))

%.o : %.cpp
	g++ -I.. -I../ext_include -I ../libgasandbox $(COPTS) -c $^

%.o : ../libgasandbox/%.cpp
	g++ -I.. -I../ext_include -I ../libgasandbox $(COPTS) -c $^

gasym$(exe) : $(lobjects)
	g++ -L../lib_win32 -I.. -I../ext_include $^ $(libs) -o $@

files := $(shell ls *.ltx)
pdfs := $(files:.ltx=.pdf)

all :: $(testinc_bin)
all :: $(lobjects) gasym$(exe)
all :: $(pdfs)

latexrules := ./latex

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
