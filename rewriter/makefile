CFLAGS += -fno-rtti
CFLAGS += -g
LLVM_LIBS := core mc

#-------------------------------------------------
# local clang build related stuff:

GCCPATH=/vbs/bldsupp.linux1/linuxamd64/gcc-4.2.2-31309

LDFLAGS += -Wl,-rpath,$(GCCPATH)/lib64
LDFLAGS += -Wl,-rpath-link,$(GCCPATH)/lib64

CXX := $(GCCPATH)/bin/g++

#-------------------------------------------------
# Built two versions of clang, one for debugging
# into rewritersample.cpp:
#-------------------------------------------------
CONFIG_RELEASE = Debug+Asserts
CLANGPATH=$(HOME)/clang/debug
#-------------------------------------------------
#CONFIG_RELEASE = Release+Asserts
#CLANGPATH=$(HOME)/clang/optimized
#-------------------------------------------------

LLVM_BIN_PATH = $(CLANGPATH)/bin
LLVM_CONFIG_COMMAND := $(LLVM_BIN_PATH)/llvm-config --cxxflags --ldflags --libs $(LLVM_LIBS)
LLVM_CONFIG_OUT := $(shell $(LLVM_CONFIG_COMMAND))

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
LLVM_CONFIG_OUT := $(subst -O3,,$(LLVM_CONFIG_OUT))
#-------------------------------------------------

CLANGLIBS += -lclangFrontendTool -lclangFrontend -lclangDriver 
CLANGLIBS += -lclangSerialization -lclangCodeGen -lclangParse 
CLANGLIBS += -lclangSema -lclangStaticAnalyzerFrontend 
CLANGLIBS += -lclangStaticAnalyzerCheckers -lclangStaticAnalyzerCore 
CLANGLIBS += -lclangAnalysis -lclangARCMigrate 
CLANGLIBS += -lclangRewriteCore 
CLANGLIBS += -lclangEdit -lclangAST -lclangLex -lclangBasic
CLANGLIBS += -lLLVMMCParser

all: rewritersample

rewritersample: rewritersample.cpp
	$(CXX) rewritersample.cpp $(CFLAGS) -o rewritersample $(CLANG_BUILD_FLAGS) $(CLANGLIBS) $(LLVM_CONFIG_OUT) $(LDFLAGS)

clean:
	rm -rf *.o *.ll rewritersample
