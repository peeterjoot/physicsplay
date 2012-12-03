//-------------------------------------------------------------------------
//
// classvisitor.cpp: AST visitor code to get info about structure fields with Clang
//
// Based on Eli Bendersky's rewritersample.cpp
//
#include <string>
#include <vector>
#include <iostream>
#include <getopt.h> // gnu getopt assumed.
#include <cstdio>
#include <cstdlib>  // exit

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
#include "clang/Frontend/TextDiagnosticPrinter.h"
#include "clang/Lex/HeaderSearch.h"
#include "clang/AST/ASTContext.h"
#include "clang/Frontend/Utils.h" // InitializePreprocessor
#include <getopt.h>

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

      cout << t->getName().str() << " : " << q.getAsString() << endl ;

      return true ;
   }

   // Find class/struct/unions:
   bool VisitCXXRecordDecl( CXXRecordDecl* r )
   {
//      cout << "VisitCXXRecordDecl:: CLASS: " << r->getName().str() << endl ;

      for ( CXXRecordDecl::base_class_iterator b = r->bases_begin(), e = r->bases_end() ;
            b != e ; ++b )
      {
         CXXBaseSpecifier & a = *b ;

         const QualType & q = a.getType() ;

         cout << r->getName().str() << " : " << q.getAsString() << endl ;
//         cout << "BASE CLASS: " << q.getAsString() << endl ;
      }

      return true ;
   }

   // Member's within class/struct/union:
   bool VisitFieldDecl( FieldDecl * f )
   {
      RecordDecl * r = f->getParent() ;
//      cout << "CLASS: " << r->getName().str() << endl ;
//      cout << "MEMBER: " << f->getName().str() << " ( " ;

      TypeSourceInfo * t = f->getTypeSourceInfo() ;

      TypeLoc TL = t->getTypeLoc() ;

      // don't care if it's an array, just want the basic underlying type of the array.
      if ( const ArrayTypeLoc *Arr = dyn_cast<ArrayTypeLoc>(&TL) )
      {
         TL = Arr->getElementLoc() ;
      }

      const QualType & q = TL.getType() ;
//      cout << "TYPE: " << q.getAsString() << " )" << endl ;

// FIXME: want to prune the struct/union/class from here:
      cout << r->getName().str() << " : " << q.getAsString() << endl ;

#if 0
      const QualType & qu = q.getDesugaredType( ci.getASTContext() ) ;
      cout << "TYPE: " << qu.getAsString() << " )" << endl ;
#endif

      return true ;
   }
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

void printUsageAndExit( const char * argv0 )
{
   printf( "%s [-Ipath | --include=path] [-Dval | --define=val] [-h | --help] filename.cpp\n"
           "\n"
           "\tExample: %s x.cpp -Ipath1 -Dfoo -Dhoo --include=path2\n"
           , argv0
           , argv0 ) ;

   exit( 1 ) ;
}

// clang env setup based on clangtut/tutorial6.cpp
int main( int argc, char * argv[] )
{
   struct option options[] =
   {
       {"include", 1, 0, 'I'}
      ,{"define", 1, 0, 'D'}
      ,{"help", 1, 0, 'h'}
   } ;

   int c = 0 ;
   int optindex = 0 ;
   vector<string> includes ;
   vector<string> defines ;

   while ( ( c = getopt_long(argc, argv, "I:D:h", options, &optindex ) ) != EOF )
   {
      switch (c)
      {
         case 'I':
         {
            includes.push_back( optarg ) ;
            //printf( "-I : %s\n", optarg ) ;
            break ;
         }
         case 'D':
         {
            defines.push_back( optarg ) ;
            //printf( "-D : %s\n", optarg ) ;
            break ;
         }

         case 'h':
         default:
         {
            printUsageAndExit( argv[0] ) ;
         }
      }
   }

   if ( optind != (argc - 1) )
   {
      printUsageAndExit( argv[0] ) ;
   }
 
   DiagnosticOptions diagnosticOptions ;

   TextDiagnosticPrinter * pTextDiagnosticPrinter 
      = new TextDiagnosticPrinter( llvm::outs(),
                                   &diagnosticOptions ) ;

   llvm::IntrusiveRefCntPtr<DiagnosticIDs> pDiagIDs ;

   DiagnosticsEngine * pDiagnosticsEngine 
      = new DiagnosticsEngine( pDiagIDs,
                               &diagnosticOptions,
                               pTextDiagnosticPrinter ) ;

   LangOptions languageOptions ;

   // Allow C++ code (https://github.com/loarabia/Clang-tutorial/blob/master/CIrewriter.cpp)
   languageOptions.GNUMode = 1 ;
   languageOptions.CXXExceptions = 1 ;
   languageOptions.RTTI = 1 ;
   languageOptions.Bool = 1 ;
   languageOptions.CPlusPlus = 1 ;

   FileSystemOptions fileSystemOptions ;

   FileManager fileManager( fileSystemOptions ) ;

   SourceManager sourceManager( *pDiagnosticsEngine,
                                fileManager ) ;

   llvm::IntrusiveRefCntPtr<HeaderSearchOptions> headerSearchOptions( new HeaderSearchOptions() ) ;

   for ( vector<string>::iterator i = includes.begin() ; i != includes.end(); ++i )
   {
      //cout << "processing -I" << *i << endl ;
      headerSearchOptions->AddPath( *i,
                                    frontend::Quoted,
                                    true,
                                    false,
                                    false ) ;
   }

   TargetOptions targetOptions ;

   targetOptions.Triple = llvm::sys::getDefaultTargetTriple() ;

   TargetInfo * pTargetInfo = TargetInfo::CreateTargetInfo( *pDiagnosticsEngine,
                                                            &targetOptions ) ;

   HeaderSearch headerSearch( headerSearchOptions,
                              fileManager,
                              *pDiagnosticsEngine,
                              languageOptions,
                              pTargetInfo ) ;

   CompilerInstance compInst ;

   llvm::IntrusiveRefCntPtr<PreprocessorOptions> pOpts( new PreprocessorOptions() ) ;

   Preprocessor preprocessor( pOpts,
                              *pDiagnosticsEngine,
                              languageOptions,
                              pTargetInfo,
                              sourceManager,
                              headerSearch,
                              compInst ) ;

   FrontendOptions frontendOptions ;

   InitializePreprocessor( preprocessor,
                           *pOpts,
                           *headerSearchOptions,
                           frontendOptions ) ;
       
   const FileEntry * pFile = fileManager.getFile( argv[optind] ) ;
   
   if ( pFile )
   {
      sourceManager.createMainFileID( pFile ) ;

      const TargetInfo &targetInfo = *pTargetInfo ;

      IdentifierTable identifierTable( languageOptions ) ;

      SelectorTable selectorTable ;

      Builtin::Context builtinContext ;

      builtinContext.InitializeTarget( targetInfo ) ;

      ASTContext astContext( languageOptions,
                             sourceManager,
                             pTargetInfo,
                             identifierTable,
                             selectorTable,
                             builtinContext,
                             0 /* size_reserve*/ ) ;

      MyASTConsumer astConsumer( compInst ) ;

#if 0
      Sema sema( preprocessor,
                 astContext,
                 astConsumer ) ;
#endif

      pTextDiagnosticPrinter->BeginSourceFile( languageOptions, &preprocessor ) ;

      ParseAST( preprocessor, &astConsumer, astContext ) ;

      pTextDiagnosticPrinter->EndSourceFile() ;
   }

   return 0 ;
}
