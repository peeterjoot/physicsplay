# don't think this is needed.  llvm-config returns it
#CFLAGS += -fno-rtti
CFLAGS += -g
LLVM_LIBS := core mc

HOSTNAME := $(shell hostname)

include makefile.$(HOSTNAME)

LLVM_CONFIG_COMMAND := $(LLVM_BIN_PATH)llvm-config --cxxflags --ldflags --libs $(LLVM_LIBS)
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

EXES += classvisitor
#EXES += rewritersample

all: $(EXES)

rewritersample: rewritersample.cpp
	$(CXX) rewritersample.cpp $(CFLAGS) -o rewritersample $(CLANG_BUILD_FLAGS) $(CLANGLIBS) $(LLVM_CONFIG_OUT) $(LDFLAGS)

classvisitor: classvisitor.cpp
	$(CXX) classvisitor.cpp $(CFLAGS) -o classvisitor $(CLANG_BUILD_FLAGS) $(CLANGLIBS) $(LLVM_CONFIG_OUT) $(LDFLAGS)

clean:
	rm -rf *.o *.ll classvisitor 
