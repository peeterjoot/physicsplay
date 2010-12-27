OBJ := obj
EXE := .exe

GASANDDIR := ../../gasand/ga2/ga_sandbox-1.0.7
GASANDLIBDIR := $(GASANDDIR)/libgasandbox
GASANDPATH += $(GASANDLIBDIR)/libgasandbox_a-

LIBGASANDOBJ += $(GASANDPATH)glut_util.$(OBJ)
LIBGASANDOBJ += $(GASANDPATH)gl_util.$(OBJ)
LIBGASANDOBJ += $(GASANDPATH)e2ga.$(OBJ)
LIBGASANDOBJ += $(GASANDPATH)c3ga.$(OBJ)
LIBGASANDOBJ += $(GASANDPATH)e3ga.$(OBJ)

CXXFLAGS := /Zi -DWIN32 /EHsc /nologo -I$(GASANDDIR)
#-I$(GASANDDIR)/include

#-DPACKAGE_NAME=\"\" -DPACKAGE_TARNAME=\"\" -DPACKAGE_VERSION=\"\" -DPACKAGE_STRING=\"\" -DPACKAGE_BUGREPORT=\"\" -DPACKAGE=\"ga_sandbox\" -DVERSION=\"1.0.7\" 

COMPILE = CL $(CXXFLAGS) /c /Fo$*.$(OBJ)
LINK = CL /nologo /Fe$@

all : juliaFractal$(EXE) freeglut.dll

juliaFractal$(EXE) : juliaFractal.obj
	$(LINK) $^ $(LIBGASANDOBJ) freeglut.lib

%.$(OBJ) : %.cpp
	$(COMPILE) $*.cpp

freeglut.dll :
	cp -i ../../gasand/freeglut-2.6.0/VisualStudio2008/debug/freeglut.dll .

clean :
	rm -f *.obj *.exe *.pdb *.dll

# other libgasandbox/ objects that also compiled:
#c2ga
#c2gatoc3ga
#c2ga_draw
#c2ga_util
#c3ga_draw
#c3ga_util
#draw
#e2ga_draw
#e3ga_draw
#e3ga_util
#geosphere
#h3ga
#h3ga_draw
#h3ga_util
#mv_analyze
#mv_analyze_c2ga
#mv_analyze_c3ga
#mv_analyze_e2ga
#mv_analyze_e3ga
#mv_analyze_h3ga
#timing
