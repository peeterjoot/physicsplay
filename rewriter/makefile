#CFLAGS += -ferror-limit=200
CFLAGS += -g
LLVM_LIBS := core mc

HOSTNAME := $(shell hostname)

include makefile.$(HOSTNAME)

CFLAGS += $(shell $(LLVM_BIN_PATH)llvm-config --cxxflags)
#CFLAGS := $(filter-out -fno-exceptions,$(CFLAGS))
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
LDFLAGS += -lLLVMBitReader

LDFLAGS += $(shell $(LLVM_BIN_PATH)llvm-config --libs $(LLVM_LIBS))

EXES += classvisitor
EXES += globalvisitor
EXES += rewriter
EXES += testit
EXES += dumper
EXES += memberdumper
EXES += LockUnlockChecker.so
CLEAN_EXES += rewritersample

CFLAGS += -std=c++11

all: $(EXES)

classvisitor.o : classvisitor.h visitor.h isystem.h depmap.h
globalvisitor.o : classvisitor.h globalcons.h isystem.h
rewriter.o : classvisitor.h rewriter.h isystem.h
dumper.o : classvisitor.h dumper.h isystem.h
memberdumper.o : classvisitor.h memberdumper.h isystem.h

%.o : %.cpp
	$(CXX) -c $< $(CFLAGS)

testit: testit.o
	$(CXX) $< -o $@ $(LDFLAGS)

dumper: dumper.o
	$(CXX) $< -o $@ $(LDFLAGS)

classvisitor: classvisitor.o
	$(CXX) $< -o $@ $(LDFLAGS)

memberdumper: memberdumper.o
	$(CXX) $< -o $@ $(LDFLAGS)

rewriter: rewriter.o
	$(CXX) $< -o $@ $(LDFLAGS)

globalvisitor: globalvisitor.o
	$(CXX) $< -o $@ $(LDFLAGS)

rewritersample: rewritersample.o
	$(CXX) $< -o $@ $(LDFLAGS)

#	g++ -shared -fPIC `llvm-config --cxxflags` -I`llvm-config --src-root`/tools/clang/include \
#		-I`llvm-config --obj-root`/tools/clang/include -o LockUnlockChecker.so LockUnlockChecker.cpp
#
LockUnlockChecker.so: LockUnlockChecker.o
	$(CXX) -shared $< -o $@ $(LDFLAGS)

isystem.h : isystem.pl
	$< $(CXX) > $@

clean:
	rm -rf *.o *.ll $(EXES) $(CLEAN_EXES) isystem.h
