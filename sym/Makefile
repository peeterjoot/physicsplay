exe := .exe

aux := ../libgasandbox/e3ga.cpp
source := $(aux) gasym.cpp

COPTS += -g
#COPTS += -O2

objects := $(subst .cpp,.o,$(source))
lobjects := $(notdir $(objects))

#libs += wsock32.lib glut32.lib opengl32.lib glu32.lib  kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib 

#libs += libgasandbox.lib
#libs += libgasandboxparse.lib

all :: $(lobjects) gasym$(exe)

%.o : %.cpp
	g++ -I.. -I../ext_include -I ../libgasandbox $(COPTS) -c $^

%.o : ../libgasandbox/%.cpp
	g++ -I.. -I../ext_include -I ../libgasandbox $(COPTS) -c $^

gasym$(exe) : $(lobjects)
	g++ -L../lib_win32 -I.. -I../ext_include $^ $(libs) -o $@

files := $(shell ls *.ltx)
pdfs := $(files:.ltx=.pdf)

all :: $(pdfs)

latexrules := ./latex

%.pdf : %.ltx
	$(latexrules)/make_pdflatex $<

