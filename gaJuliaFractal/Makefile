OBJ := obj
EXE := .exe

GASANDBOX := ../../gasand/ga2/ga_sandbox-1.0.7
LIBGLUT := freeglut.lib

LIBGASANDBOX += ../../gasand/ga25/TestG25/e2ga_cpp/e2ga.obj

CXXFLAGS += /Zi -DWIN32 /EHsc /nologo 
CXXFLAGS += -I../../gasand/ga25/TestG25/e2ga_cpp
CXXFLAGS += -I../../gasand/ga25/TestG25/c3ga_cpp
CXXFLAGS += -I../../gasand/ga25/TestG25/e3ga_cpp
CXXFLAGS += -I.

COMPILE = CL $(CXXFLAGS) /c /Fo$*.$(OBJ)
LINK = CL /nologo /Fe$@

all :: juliaFractal$(EXE)
all :: freeglut.dll
#all :: test$(EXE)

juliaFractal_DEPS += juliaFractal.$(OBJ)
juliaFractal_DEPS += glut_util.$(OBJ)

juliaFractal$(EXE) : $(juliaFractal_DEPS)
	$(LINK) $^ $(LIBGASANDBOX) $(LIBGLUT)

test$(EXE) : test.$(OBJ)
	$(LINK) $^ $(LIBGLUT)

%.$(OBJ) : %.cpp
	$(COMPILE) $*.cpp

freeglut.dll :
	cp -i ../../gasand/freeglut-2.6.0/VisualStudio2008/debug/freeglut.dll .

clean :
	rm -f *.$(OBJ) *$(EXE) *.pdb *.dll
