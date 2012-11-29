#-------------------------------------------------
# local clang build related stuff:

LDFLAGS += -Wl,-rpath,$(HOME)/local/lib64:$(HOME)/local/lib
LDFLAGS += -Wl,-rpath-link,$(HOME)/local/lib64:$(HOME)/local/lib
LLVM_SRC_PATH = $(HOME)/tmp/clang/llvm
LLVM_BUILD_PATH = $(HOME)/tmp/clang/build
#CONFIG_RELEASE = Debug+Asserts
CONFIG_RELEASE = Release+Asserts

CFLAGS += -L$(HOME)/local/include
#LDFLAGS += -L$(HOME)/local/lib
#LDFLAGS += -L$(HOME)/local/lib64
CXX := $(HOME)/local/bin/g++
#-------------------------------------------------

#CXX = g++
CFLAGS += -fno-rtti

LLVM_BIN_PATH = $(LLVM_BUILD_PATH)/$(CONFIG_RELEASE)/bin
LLVM_LIBS=core mc
LLVM_CONFIG_COMMAND = $(LLVM_BIN_PATH)/llvm-config --cxxflags --ldflags --libs $(LLVM_LIBS)

CLANG_BUILD_FLAGS += -I$(LLVM_SRC_PATH)/tools/clang/include 
CLANG_BUILD_FLAGS += -I$(LLVM_BUILD_PATH)/tools/clang/include

LLVM_CONFIG_OUT := $(shell $(LLVM_CONFIG_COMMAND))

#-------------------------------------------------
# for debugging:

CFLAGS += -g
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
