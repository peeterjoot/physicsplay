// forked from: http://llvm.org/svn/llvm-project/cfe/branches/tooling/examples/rename-method/RenameMethod.cpp
//=- examples/rename-method/RenameMethod.cpp ------------------------------===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
// A small example tool that uses AST matchers to find calls to the Get() method
// in subclasses of ElementsBase and replaces them with calls to Front().
//
//===----------------------------------------------------------------------===//

#include "clang/ASTMatchers/ASTMatchers.h"
#include "clang/ASTMatchers/ASTMatchFinder.h"
#include "clang/Tooling/CompilationDatabase.h"
#include "clang/Tooling/Refactoring.h"
#include "llvm/Support/CommandLine.h"

using namespace clang;
using namespace clang::ast_matchers;
using namespace clang::tooling;
using namespace llvm;

cl::opt<std::string> BuildPath(
  cl::Positional,
  cl::desc("<build-path>"));

cl::list<std::string> SourcePaths(
  cl::Positional,
  cl::desc("<source0> [... <sourceN>]"),
  cl::OneOrMore);

// Implements a callback that replaces the calls for the AST
// nodes we matched.
class CallRenamer : public MatchFinder::MatchCallback {
  const char * inputName ;
  const char * replacementName ;
public:
  CallRenamer(Replacements *Replace, const char * const srcName, const char * const repName) : Replace(Replace), inputName(srcName), replacementName(repName) {}

  // This method is called every time the registered matcher matches
  // on the AST.
	virtual void run(const MatchFinder::MatchResult &Result) {
    const CallExpr *M = Result.Nodes.getStmtAs<CallExpr>(inputName);
    // We can assume M is non-null, because the ast matchers guarantee
    // that a node with this type was bound, as the matcher would otherwise
    // not match.

    if ( M )
    {
    Replace->insert(
      // Replacements are a source manager independent way to express
      // transformation on the source.
      Replacement(*Result.SourceManager,
                  // Replace the range of the member name...
                  CharSourceRange::getTokenRange(
                    SourceRange(M->getLocStart())),
                  // ... with:
                  replacementName));
    }
  }

private:
  // Replacements are the RefactoringTool's way to keep track of code
  // transformations, deduplicate them and apply them to the code when
  // the tool has finished with all translation units.
  Replacements *Replace;
};

#if 0
// Implements a callback that replaces the decls for the AST
// nodes we matched.
class DeclRenamer : public MatchFinder::MatchCallback {
public:
  DeclRenamer(Replacements *Replace) : Replace(Replace) {}

  // This method is called every time the registered matcher matches
  // on the AST.
	virtual void run(const MatchFinder::MatchResult &Result) {
    const CXXMethodDecl *D = Result.Nodes.getDeclAs<CXXMethodDecl>("method");
    // We can assume D is non-null, because the ast matchers guarantee
    // that a node with this type was bound, as the matcher would otherwise
    // not match.

    Replace->insert(
      // Replacements are a source manager independent way to express
      // transformation on the source.
      Replacement(*Result.SourceManager,
                  // Replace the range of the declarator identifier...
                  CharSourceRange::getTokenRange(
                    SourceRange(D->getLocation())),
                  // ... with "Front".
                  "Front"));
  }

private:
  // Replacements are the RefactoringTool's way to keep track of code
  // transformations, deduplicate them and apply them to the code when
  // the tool has finished with all translation units.
  Replacements *Replace;
};
#endif

int main(int argc, const char **argv) {
  // First see if we can create the compile command line from the
  // positional parameters after "--".
  OwningPtr<CompilationDatabase> Compilations(
    FixedCompilationDatabase::loadFromCommandLine(argc, argv));

  // Do normal command line handling from the rest of the arguments.
  cl::ParseCommandLineOptions(argc, argv);

  if (!Compilations) {
    // If the caller didn't specify a compile command line to use, try to
    // load it from a build directory. For example when running cmake, use
    // CMAKE_EXPORT_COMPILE_COMMANDS=ON to prepare your build directory to
    // be useable with clang tools.
    std::string ErrorMessage;
    Compilations.reset(CompilationDatabase::loadFromDirectory(BuildPath,
                                                              ErrorMessage));
    if (!Compilations)
      llvm::report_fatal_error(ErrorMessage);
  }

  RefactoringTool Tool(*Compilations, SourcePaths);
  ast_matchers::MatchFinder Finder;

  /*
   * What I really want to match to:
   *
|   `-CallExpr 0x18afa48 </view/peeterj_clang8/vbs/engn/include/sqlomem.h:444:12, line:445:47> 'sqlzRc':'int'
|     |-ImplicitCastExpr 0x18afa30 <line:444:12> 'sqlzRc (*)(SQLO_MEM_POOL_HANDLE, const size_t, Uint32, void **, const char *, const Uint, SQLO_RESOURCE_HANDLE)' <FunctionToPointerDecay>
|     | `-DeclRefExpr 0x18afa08 <col:12> 'sqlzRc (SQLO_MEM_POOL_HANDLE, const size_t, Uint32, void **, const char *, const Uint, SQLO_RESOURCE_HANDLE)' lvalue Function 0x18a8d80 'sqlogmblkEx' 'sqlzRc (SQLO_MEM_POOL_HANDLE, const size_t, Uint32, void **, const char *, const Uint, SQLO_RESOURCE_HANDLE)'

   */
  CallRenamer gmblkCallCallback(&Tool.getReplacements(), "myfunc", "xxmyfunc");
  Finder.addMatcher(
        callExpr( callee(functionDecl(hasName("myfunc")))).bind("myfunc"),
    &gmblkCallCallback);

#if 0
  CallRenamer gmblkCallCallback(&Tool.getReplacements(), "sqlogmblk", "xxsqlogmblk");
  Finder.addMatcher(
        callExpr( callee(functionDecl(hasName("sqlogmblk")))).bind("sqlogmblk"),
    &gmblkCallCallback);

  CallRenamer gblkCallCallback(&Tool.getReplacements(), "sqlogblk", "xxsqlogblk");

  Finder.addMatcher(
        callExpr( callee(functionDecl(hasName("sqlogblk")))).bind("sqlogblk"),
    &gblkCallCallback);
#endif

#if 0
  Finder.addMatcher(
    // Match calls...
    memberCallExpr(
      // Where the callee is a method called "Get"...
      callee(methodDecl(hasName("Get"))),
      // ... and the class on which the method is called is derived
      // from ElementsBase ...
      thisPointerType(recordDecl(
        isDerivedFrom("ElementsBase"))),
      // ... and bind the member expression to the ID "member", under which
      // it can later be found in the callback.
      callee(id("member", memberExpr()))),
    &CallCallback);

  DeclRenamer DeclCallback(&Tool.getReplacements());
  Finder.addMatcher(
    // Match declarations...
    id("method", methodDecl(hasName("Get"),
                        ofClass(isDerivedFrom("ElementsBase")))),
    &DeclCallback);

  Finder.addMatcher(
    // Match calls...
    memberCallExpr(
      // Where the callee is a method called "Get"...
      callee(methodDecl(hasName("Get"))),
      // ... and the class on which the method is called is derived
      // from ElementsBase ...
      thisPointerType(recordDecl(
        isDerivedFrom("ElementsBase"))),
      // ... and bind the member expression to the ID "member", under which
      // it can later be found in the callback.
      callee(id("member", memberExpr()))),
    &CallCallback);
#endif

  return Tool.runAndSave(newFrontendActionFactory(&Finder));
}
