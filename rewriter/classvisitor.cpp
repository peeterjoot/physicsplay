//-------------------------------------------------------------------------
//
// classvisitor.cpp: AST visitor code to get info about structure fields with Clang
//
// Based on Eli Bendersky's rewritersample.cpp
//
#include <cstdio>
#include <string>
#include <cassert>
#include <cstdlib>
#include <sstream>
#include <iostream>

#include "clang/AST/ASTConsumer.h"
#include "clang/AST/RecursiveASTVisitor.h"
#include "clang/Basic/Diagnostic.h"
#include "clang/Basic/FileManager.h"
#include "clang/Basic/SourceManager.h"
#include "clang/Basic/TargetOptions.h"
#include "clang/Basic/TargetInfo.h"
#include "clang/Basic/LangOptions.h"
#include "clang/Frontend/CompilerInstance.h"
#include "clang/Lex/Preprocessor.h"
#include "clang/Parse/ParseAST.h"
#include "llvm/Support/Host.h"
#include "llvm/Support/raw_ostream.h"

using namespace clang ;
using namespace std ;

// By implementing RecursiveASTVisitor, we can specify which AST nodes
// we're interested in by overriding relevant methods.
class MyASTVisitor : public RecursiveASTVisitor<MyASTVisitor>
{
   CompilerInstance & ci ;

public:
   MyASTVisitor( CompilerInstance & ci_ ) : ci(ci_)
   {}

   // Find typedefs:
   bool VisitTypedefDecl( TypedefDecl * t )
   {
      const QualType & q = t->getUnderlyingType() ;

      cout << t->getName().str() << " -> " << q.getAsString() << endl ;

      return true ;
   }

   // Find class/struct/unions:
   bool VisitCXXRecordDecl( CXXRecordDecl* r )
   {
      cout << "VisitCXXRecordDecl:: CLASS: " << r->getName().str() << endl ;

      for ( CXXRecordDecl::base_class_iterator b = r->bases_begin(), e = r->bases_end() ;
            b != e ; ++b )
      {
         CXXBaseSpecifier & a = *b ;

         const QualType & q = a.getType() ;

         cout << "BASE CLASS: " << q.getAsString() << endl ;
      }

      return true ;
   }

   // Member's within class/struct/union:
   bool VisitFieldDecl( FieldDecl * f )
   {
      RecordDecl * r = f->getParent() ;
      cout << "CLASS: " << r->getName().str() << endl ;
      cout << "MEMBER: " << f->getName().str() << " ( " ;

      TypeSourceInfo * t = f->getTypeSourceInfo() ;

      TypeLoc TL = t->getTypeLoc() ;

      // don't care if it's an array, just want the basic underlying type of the array.
      if ( const ArrayTypeLoc *Arr = dyn_cast<ArrayTypeLoc>(&TL) )
      {
         TL = Arr->getElementLoc() ;
      }

      const QualType & q = TL.getType() ;
      const QualType & qu = q.getDesugaredType( ci.getASTContext() ) ;

      // for SVC, probably want both sugared and non-sugared types:
      //cout << "TYPE: " << q.getAsString() << " )" << endl ;
      cout << "TYPE: " << qu.getAsString() << " )" << endl ;

      return true ;
   }
#if 0
      //QualType CanonicalType = q.getTypePtr()->CanonicalType ;
      //if ( CanonicalType.isScalarType( ) ) // private.
      if ( q.isTrivialType( ci.getASTContext() ) )
      {
         cout << "SCALAR " ;
      }
#endif

} ;

// Implementation of the ASTConsumer interface for reading an AST produced
// by the Clang parser.
class MyASTConsumer : public ASTConsumer
{
public:
   MyASTConsumer( CompilerInstance & ci_ ) : Visitor(ci_) {}

   // Override the method that gets called for each parsed top-level
   // declaration.
   virtual bool HandleTopLevelDecl(DeclGroupRef DR)
   {
      for (DeclGroupRef::iterator b = DR.begin(), e = DR.end() ;
          b != e ; ++b)
      {
         // Traverse the declaration using our AST visitor.
         Visitor.TraverseDecl(*b) ;
      }

      return true ;
   }

private:
   MyASTVisitor Visitor ;
} ;


int main(int argc, char *argv[])
{
   if (argc != 2)
   {
      llvm::errs() << "Usage: rewritersample <filename>\n" ;
      return 1 ;
   }

   // CompilerInstance will hold the instance of the Clang compiler for us,
   // managing the various objects needed to run the compiler.
   CompilerInstance TheCompInst ;
   TheCompInst.createDiagnostics(0, 0) ;

   // Initialize target info with the default triple for our platform.
   TargetOptions * TO = new TargetOptions ;
   TO->Triple = llvm::sys::getDefaultTargetTriple() ;
   TargetInfo *TI = TargetInfo::CreateTargetInfo(
      TheCompInst.getDiagnostics(), TO) ;
   TheCompInst.setTarget(TI) ;

   TheCompInst.createFileManager() ;
   FileManager &FileMgr = TheCompInst.getFileManager() ;
   TheCompInst.createSourceManager(FileMgr) ;
   SourceManager &SourceMgr = TheCompInst.getSourceManager() ;

   // Allow C++ code (https://github.com/loarabia/Clang-tutorial/blob/master/CIrewriter.cpp)
   TheCompInst.getLangOpts().GNUMode = 1 ; 
   TheCompInst.getLangOpts().CXXExceptions = 1 ; 
   TheCompInst.getLangOpts().RTTI = 1 ; 
   TheCompInst.getLangOpts().Bool = 1 ; 
   TheCompInst.getLangOpts().CPlusPlus = 1 ; 
 
   TheCompInst.createPreprocessor() ;
   TheCompInst.createASTContext() ;

   // Set the main file handled by the source manager to the input file.
   const FileEntry *FileIn = FileMgr.getFile(argv[1]) ;

   if ( FileIn )
   {
      SourceMgr.createMainFileID(FileIn) ;

      TheCompInst.getDiagnosticClient().BeginSourceFile(
         TheCompInst.getLangOpts(),
         &TheCompInst.getPreprocessor()) ;

      // Create an AST consumer instance which is going to get called by
      // ParseAST.
      MyASTConsumer TheConsumer( TheCompInst ) ;

      // Parse the file to AST, registering our consumer as the AST consumer.
      ParseAST(TheCompInst.getPreprocessor(), &TheConsumer,
            TheCompInst.getASTContext()) ;
   }

   return 0 ;
}
