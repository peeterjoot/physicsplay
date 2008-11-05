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

all : $(lobjects) gasym$(exe)

%.o : %.cpp
	g++ -I.. -I../ext_include -I ../libgasandbox $(COPTS) -c $^

%.o : ../libgasandbox/%.cpp
	g++ -I.. -I../ext_include -I ../libgasandbox $(COPTS) -c $^

gasym$(exe) : $(lobjects)
	g++ -L../lib_win32 -I.. -I../ext_include $^ $(libs) -o $@

#cl /O2 /I "..\\" /I "..\ext_include" /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /D "_VC80_UPGRADE=0x0710" /D "_MBCS" /FD /EHsc /MT /Fo"chap1ex1_Release\\" /Fd"chap1ex1_Release\vc80.pdb" /W3 /nologo /c /Wp64 /Zi /TP /errorReport:prompt

#/OUT:"Release/chap1ex1.exe" /INCREMENTAL:NO /NOLOGO /LIBPATH:"..\lib_win32" /MANIFEST /MANIFESTFILE:"chap1ex1_Release\chap1ex1.exe.intermediate.manifest" /DEBUG /PDB:"c:\Documents and Settings\peeterj\ga\ga_sandbox-1.0.5\vs2005\release\chap1ex1.pdb" /SUBSYSTEM:CONSOLE /OPT:REF /OPT:ICF /MACHINE:X86 /ERRORREPORT:PROMPT 
