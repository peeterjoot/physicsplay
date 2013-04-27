// forked basic infrastructure for a "renamer"
//
// from: http://llvm.org/svn/llvm-project/cfe/branches/tooling/examples/rename-method/RenameMethod.cpp
//
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
#include "clang/Basic/SourceManager.h"
#include "clang/Lex/Lexer.h"
#include <iostream>

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

// original RenameMethod.cpp callbacks:
#if 0
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

// http://stackoverflow.com/a/11154162/189270
std::string decl2str( const Expr *d, const SourceManager *sm )
{
   std::string r ;
   SourceLocation _b(d->getLocStart()), _e(d->getLocEnd());

   if ( _b.isValid() && _e.isValid() )
   {
     // This is the default LangOptions... not sure how to get the LangOptions that must have
     // been supplied in newFrontendActionFactory() somewhere along the way
     LangOptions lopt;

     SourceLocation b(clang::Lexer::getLocForEndOfToken(_b, 0, *sm, lopt));
     SourceLocation e(clang::Lexer::getLocForEndOfToken(_e, 0, *sm, lopt));
  
     const char * bs ;
     const char * es ;
     ptrdiff_t d ;

     if ( b.isValid() && e.isValid() )
     {
        bs = sm->getCharacterData(b) - 1 ;
        es = sm->getCharacterData(e) ;
        d = es - bs ;
     }
     else
     {
        bs = sm->getCharacterData(_b) ;
        es = sm->getCharacterData(_e) ;
        d = es - bs + 1 ;
     }

     r = std::string( bs, d ) ;
  
     //std::cout << "e: " << r << std::endl ;
     //d->dump() ;
   }
   else if ( 0 )
   {
      std::cout << "x: " << r << std::endl ;
      d->dump() ;
       abort() ;
   }

   return r ;
}

class gmblkModifier : public MatchFinder::MatchCallback {
public:
  gmblkModifier(Replacements *Replace) : Replace(Replace) {}

  // This method is called every time the registered matcher matches
  // on the AST.
  virtual void run(const MatchFinder::MatchResult &Result) {
    const CallExpr *M = Result.Nodes.getStmtAs<CallExpr>("x");
    const Expr * a = M->getArg( 3 ) ;

    // strip out the (presumed 'void **' casting) in sqlogmblk calls.
    if ( const CStyleCastExpr * v = dyn_cast<CStyleCastExpr>( a ) )
    {
#if 0
std::cout << "M: " << decl2str( M, Result.SourceManager ) << std::endl ;
    M->dump() ;
std::cout << "a: " << decl2str( a, Result.SourceManager ) << std::endl ;
    a->dump() ;
std::cout << "v: " << decl2str( v, Result.SourceManager ) << std::endl ;
    v->dump() ;
#endif
      const Expr * theCastedValue = v->getSubExprAsWritten() ;
      //theCastedValue->dump() ;
      //std::cout << v->getCastKindName() << std::endl ; // -> CK_BitCast 

      if ( theCastedValue )
      {
        std::string replacement = decl2str( theCastedValue, Result.SourceManager ) ; 
 
        if ( replacement.length() )
        {
          std::string orig = decl2str( a, Result.SourceManager ) ;
std::cout << "r: '" << replacement << "' -> '" << orig << "'\n" ;

          Replace->insert(
            Replacement(*Result.SourceManager,
                        a->getLocStart(),
                        orig.length(),
                        replacement)
            ) ;
        } 
      }
    }
  }

private:
  // Replacements are the RefactoringTool's way to keep track of code
  // transformations, deduplicate them and apply them to the code when
  // the tool has finished with all translation units.
  Replacements *Replace;

};

class gblkModifier : public MatchFinder::MatchCallback {
public:
  gblkModifier(Replacements *Replace) : Replace(Replace) {}

  // This method is called every time the registered matcher matches
  // on the AST.
  virtual void run(const MatchFinder::MatchResult &Result) {
    const CallExpr *M = Result.Nodes.getStmtAs<CallExpr>("y");
    //M->dump() ;
    const Expr * a = M->getArg( 2 ) ;

    // 
    // shortening and lengthening in two separate replacements isn't working in some situations:
    //     -   rc = sqlogblk(heapptr, size, (void **)replypp);
    //     +   rc = sqlogmblk(heapptr, size, SQLO_MEM_DEFAULT, p);
    //
    // but works fine for some reason if I copy this standalone?
    //
    // ... probably ought to be doing a single pass replacement of the whole call, renaming, inserting param, and removing the cast.
    //
    // For now, thought I may have to settle for two passes, but the other Matcher for gmblk actually kicks in after this one!
    //
        std::string replacement = decl2str( a, Result.SourceManager ) ; 
 
        if ( replacement.length() )
        {
          replacement = "SQLO_MEM_DEFAULT, " + replacement ;
   
          // rename the function:
          Replace->insert(
            Replacement(*Result.SourceManager,
                        CharSourceRange::getTokenRange(
                          SourceRange(M->getLocStart())),
                        "sqlogmblk"));
    
          // and insert the SQLO_MEM_DEFAULT param
          std::string orig = decl2str( a, Result.SourceManager ) ;

          Replace->insert(
            Replacement(*Result.SourceManager,
                        a->getLocStart(),
                        orig.length(),
                        replacement)
            ) ;
        }
#if 0
    // strip out the (presumed 'void **' casting) in sqlogblk calls.
    if ( const CStyleCastExpr * v = dyn_cast<CStyleCastExpr>( a ) )
    {
      //v->dump() ;
      const Expr * theCastedValue = v->getSubExprAsWritten() ;
      //theCastedValue->dump() ;

      if ( theCastedValue )
      {
        std::string replacement = decl2str( theCastedValue, Result.SourceManager ) ; 
 
        if ( replacement.length() )
        {
          replacement = "SQLO_MEM_DEFAULT, " + replacement ;
    
          // rename the function:
          Replace->insert(
            Replacement(*Result.SourceManager,
                        CharSourceRange::getTokenRange(
                          SourceRange(M->getLocStart())),
                        "sqlogmblk"));
    
          // and insert the SQLO_MEM_DEFAULT param, and strip the void ** cast:
          std::string orig = decl2str( a, Result.SourceManager ) ;

          Replace->insert(
            Replacement(*Result.SourceManager,
                        a->getLocStart(),
                        orig.length(),
                        replacement)
            ) ;
        }
      }
    }
#endif
  }

private:
  // Replacements are the RefactoringTool's way to keep track of code
  // transformations, deduplicate them and apply them to the code when
  // the tool has finished with all translation units.
  Replacements *Replace;
};


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

  gmblkModifier gmblkCallBack(&Tool.getReplacements());
  Finder.addMatcher(
        callExpr( callee(functionDecl(hasName("sqlogmblk"))) ).bind("x"),
    &gmblkCallBack);

  gblkModifier gblkCallBack(&Tool.getReplacements());
  Finder.addMatcher(
        callExpr( callee(functionDecl(hasName("sqlogblk"))) ).bind("y"),
    &gblkCallBack);

  Finder.addMatcher(
        callExpr( callee(functionDecl(hasName("sqlogtblk"))) ).bind("y"),
    &gblkCallBack);

// original RenameMethod.cpp matchers (modified for current clang source):
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
