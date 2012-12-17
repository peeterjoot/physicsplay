CFLAGS += -g
LLVM_LIBS := core mc

HOSTNAME := $(shell hostname)

include makefile.$(HOSTNAME)

CFLAGS += $(shell $(LLVM_BIN_PATH)llvm-config --cxxflags)
LDFLAGS += $(shell $(LLVM_BIN_PATH)llvm-config --ldflags)

# HACK: llvm-config doesn't get along with clearcase as an install path and appears to be picking out my view storage dir.
#
# http://stackoverflow.com/questions/13650862/result-from-proc-self-exe-is-unfriendly-in-a-clearcase-view/13651141#13651141
#
# (dealt with this by avoiding an install in /vbs/ for now).
#
#LLVM_CONFIG_OUT := $(subst /home/hotellnx99/peeterj/views/peeterj_clang-7.vws/.s,$(CLANGPATH),$(LLVM_CONFIG_OUT))

#-------------------------------------------------
# for debugging:

# for Release+Asserts config:
CFLAGS := $(subst -O3,,$(CFLAGS))
#-------------------------------------------------

LDFLAGS += -lclangFrontendTool -lclangFrontend -lclangDriver 
LDFLAGS += -lclangSerialization -lclangCodeGen -lclangParse 
LDFLAGS += -lclangSema -lclangStaticAnalyzerFrontend 
LDFLAGS += -lclangStaticAnalyzerCheckers -lclangStaticAnalyzerCore 
LDFLAGS += -lclangAnalysis -lclangARCMigrate 
LDFLAGS += -lclangRewriteCore 
LDFLAGS += -lclangEdit -lclangAST -lclangLex -lclangBasic
LDFLAGS += -lLLVMMCParser

LDFLAGS += $(shell $(LLVM_BIN_PATH)llvm-config --libs $(LLVM_LIBS))

EXES += classvisitor
EXES += globalvisitor
EXES += testit
#EXES += rewritersample

CFLAGS += -std=c++11

all: $(EXES)

classvisitor.o : classvisitor.h
globalvisitor.o : classvisitor.h

%.o : %.cpp
	$(CXX) -c $< $(CFLAGS)

testit: testit.o
	$(CXX) $< -o $@ $(LDFLAGS)

classvisitor: classvisitor.o
	$(CXX) $< -o $@ $(LDFLAGS)

globalvisitor: globalvisitor.o
	$(CXX) $< -o $@ $(LDFLAGS)

rewritersample: rewritersample.o
	$(CXX) $< -o $@ $(LDFLAGS)

clean:
	rm -rf *.o *.ll classvisitor globalvisitor rewritersample
