//-------------------------------------------------------------------------
//
// classvisitor.cpp: AST visitor code to get info about structure fields with Clang
//
// The MyASTVisitor and driver was initially based on Eli Bendersky's rewritersample.cpp.
//
// Later gutted the driver and replaced with one based on:
//
//    https://github.com/loarabia/Clang-tutorial/blob/master/tutorial6.cpp
//
// As is this code can be used to answer two types of questions:
//
// 1) What dependencies does a class/struct/union have.  Raw output
//    includes enough info that one could build a dependency tree for a given type.
//
// 2) Identify all global variables and their types, and cross reference that with the class/struct's dependency info (from above) 
//    to see what global variables use explicit constructors.  This is for finding where specifically a C++ global constructor
//    is coming from when this are problematic (i.e. this is a restriction of libdb2.a and if you accidentally add a constructor
//    it can be hard to figure out the exact global it came from.)
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
#include "clang/Rewrite/Core/Rewriter.h"
#if defined REWRITER
   #include <sstream>
#endif

using namespace clang ;
using namespace std ;

#if defined CLASSVISITOR
   const char * g_symbolfile = NULL ;
   string g_typeSuppressed( "<>" ) ;

   #include "depmap.h"
#endif

inline QualType getQualTypeForDecl( DeclaratorDecl * f )
{
   TypeSourceInfo * pThisFieldSourceInfo = f->getTypeSourceInfo() ;

   TypeLoc thisFieldTypeLoc = pThisFieldSourceInfo->getTypeLoc() ;

   // don't care if it's an array, just want the basic underlying type of the array.
   for ( ; ; )
   {
      if ( ArrayTypeLoc TypeLocIfArray = thisFieldTypeLoc.getAs<ArrayTypeLoc>() )
      {
         thisFieldTypeLoc = TypeLocIfArray.getElementLoc() ;
      }
      else
      {
         break ;
      }
   } 

   return thisFieldTypeLoc.getType() ;
}

static QualType returnUnderlyingTypeIfArray( QualType q )
{
   const Type *   tUnderlying = q.getTypePtr() ;

   if ( tUnderlying->isArrayType() )
   {
      while ( tUnderlying->isArrayType() )
      {
         //tUnderlying->dump() ;

         tUnderlying = tUnderlying->getBaseElementTypeUnsafe() ;
      }

      q = tUnderlying->getLocallyUnqualifiedSingleStepDesugaredType() ;
   }

   return q ;
}

// By implementing RecursiveASTVisitor, we can specify which AST nodes
// we're interested in by overriding relevant methods.
class MyASTVisitor : public RecursiveASTVisitor<MyASTVisitor>
{
   CompilerInstance &            m_ci ;
   ASTContext &                  m_context ;
   PrintingPolicy                m_pp ;
   Rewriter &                    m_re ;
public:
   MyASTVisitor( CompilerInstance & ci_, Rewriter & re ) :
      m_ci( ci_ ),
      m_context( m_ci.getASTContext() ),
      m_pp( m_context.getLangOpts() ),
      m_re( re )
   {
      m_pp.SuppressTagKeyword = 1 ;
   }

#if defined GLOBALVISITOR
   #include "globalcons.h"
#endif

#if defined CLASSVISITOR
   #include "visitor.h"
#endif

#if defined MEMBERDUMPER
   #include "memberdumper.h"
#endif

#if defined REWRITER
   #include "rewriter.h"
#endif

#if defined DUMPER
   #include "dumper.h"
#endif
} ;

// Implementation of the ASTConsumer interface for reading an AST produced
// by the Clang parser.
class MyASTConsumer : public ASTConsumer
{
public:
   MyASTConsumer( CompilerInstance & ci_, Rewriter & re_ ) : Visitor( ci_, re_ ) {}

   // Override the method that gets called for each parsed top-level
   // declaration.
   virtual bool HandleTopLevelDecl(DeclGroupRef DR)
   {
      for ( DeclGroupRef::iterator b = DR.begin(), e = DR.end() ;
            b != e ; ++b )
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

int main( int argc, char * argv[] )
{
   struct option options[] =
   {
       {"include", 1, 0, 'I'}
      ,{"define", 1, 0, 'D'}
      ,{"undef", 1, 0, 'U'}
#if defined CLASSVISITOR
      ,{"verbosedeps", 0, 0, 'v'}
      ,{"symbolfile", 1, 0, 's'}
#endif
      //,{"opt-report-file", 1, 0, 'o'} // intel compiler
      ,{"help", 0, 0, 'h'}
   } ;

   int c = 0 ;
   int optindex = 0 ;

   llvm::IntrusiveRefCntPtr<PreprocessorOptions> pOpts( new PreprocessorOptions() ) ;
   llvm::IntrusiveRefCntPtr<HeaderSearchOptions> headerSearchOptions( new HeaderSearchOptions() ) ;

// 
// This handles the issues with <stdlib.h> not found ... and so forth.  However, it introduces problems with various __builtin... not found.
// Those builtins not found also appear to be able to trigger an assert in the parser:
//
//    /view/peeterj_clang-9/vbs/engn/include/trcbase.h:488:32: note: expanded from macro 'sqlt_tmp_entry'
//       #define sqlt_tmp_entry      sqlt_fnc_entry
//                                   ^
//    /view/peeterj_clang-9/vbs/engn/include/trcbase.h:393:7: note: expanded from macro 'sqlt_fnc_entry'
//          HOOK_INTO_OLD_TRACE_ENTRY(fnc) ;                                     \
//          ^
//    /view/peeterj_clang-9/vbs/engn/pd/inc/pdtraceapi.h:467:4: note: expanded from macro 'HOOK_INTO_OLD_TRACE_ENTRY'
//       TRACE_ENTRY_DEBUG_HOOK( _ecfID );      \
//       ^
//    /view/peeterj_clang-9/vbs/engn/pd/inc/pdtraceapi.h:444:4: note: expanded from macro 'TRACE_ENTRY_DEBUG_HOOK'
//       IF_TRACE_AND_DEBUG_HOOK \
//       ^
//    /view/peeterj_clang-9/vbs/engn/pd/inc/pdtraceapi.h:434:38: note: expanded from macro 'IF_TRACE_AND_DEBUG_HOOK'
//    #define IF_TRACE_AND_DEBUG_HOOK if ( OSS_HINT_MARK_BRANCH_UNLIKELY(pdTraceLocalFlag & PD_FLAG_DEBUG_HOOK))
//                                         ^
//    /view/peeterj_clang-9/vbs/common/osse/core/inc/osscompilerhints.h:77:46: note: expanded from macro 'OSS_HINT_MARK_BRANCH_UNLIKELY'
//        #define OSS_HINT_MARK_BRANCH_UNLIKELY(x) __builtin_expect((x),0)
//                                                 ^
//    /vbs/engn/include/sqlowlst_inlines.h:48:10: warning: expression result unused
//    classvisitor: /home/peeterj/clang/sources/llvm/tools/clang/lib/Basic/SourceManager.cpp:950: std::pair<clang::SourceLocation, clang::SourceLocation> clang::SourceManager::getImmediateExpansionRange(clang::SourceLocation) const: Assertion `Loc.isMacroID() && "Not a macro expansion loc!"' failed.
//    Stack dump:
//    0.      /vbs/engn/include/sqlowlst_inlines.h:48:10 <Spelling=/view/peeterj_clang-9/vbs/engn/include/trcbase.h:393:38>: current parser token ';'
//    1.      /vbs/engn/include/sqlowlst_inlines.h:47:7: parsing function body 'semaphoreOp'
//    2.      /vbs/engn/include/sqlowlst_inlines.h:47:7: in compound statement ('{}')
//    3.      /vbs/engn/include/sqlowlst_inlines.h:48:10 <Spelling=/view/peeterj_clang-9/vbs/engn/include/trcbase.h:391:4>: in compound statement ('{}')
//    4.      /vbs/engn/include/sqlowlst_inlines.h:48:10 <Spelling=/view/peeterj_clang-9/vbs/engn/pd/inc/pdtraceapi.h:464:43>: in compound statement ('{}')
//    Aborted
//
// Should report this, but producing a standalone fragment to reproduce this is tricky.
//
   //#include "isystem.h"

   for ( ; c != EOF ; )
   {
      c = getopt_long( argc,
                       argv,
                       "I:" // -Ipath | --include=path
                       "D:" // -Dval | --define=val
                       "U:" // -Uval | --undef=val
                       "h"  // -h (this driver help)
                       /* option compatibility with actual compilers: */
                       "c"  // -c
                       "W:" // -Wformat ...
                       "w:" // -we1573, -wd1901, ...
                       "O:" // -O2 -O0 ...
                       "o:" // -O2 -O0 ...
                       "m:" // -msse4.2 ...
                       "n:" // -no-ftz, -no-multibyte-chars, ...
                       "f:" // -fcheck-new ...
                       "g"  // -g
                       "",
                       options,
                       &optindex ) ;
            /* dummy args: */ 

      switch (c)
      {
#if defined CLASSVISITOR
         case 'v':
         {
            g_quietDeps = false ;

            break ;
         }
         case 's':
         {
            g_symbolfile = optarg ;

            break ;
         }
#endif
         case 'W':
         case 'w':
         case 'c':
         case 'O':
         case 'o':
         case 'm':
         case 'f':
         case 'n':
         case 'g':
         {
            /* no-op */

            break ;
         }
         case 'I':
         {
            //printf( "-I : %s\n", optarg ) ;
            headerSearchOptions->AddPath( optarg,
                                          frontend::Quoted,
                                          false, // IsFramework
                                          false ) ; // IgnoreSysRoot
            break ;
         }
         case 'D':
         {
            //printf( "-D : %s\n", optarg ) ;
            pOpts->addMacroDef( optarg ) ;

            break ;
         }
         case 'U':
         {
            //printf( "-U : %s\n", optarg ) ;
            pOpts->addMacroUndef( optarg ) ;

            break ;
         }

         case EOF:
         {
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
   languageOptions.GNUMode          = 1 ;
   languageOptions.CXXExceptions    = 1 ;
   languageOptions.RTTI             = 1 ;
   languageOptions.Bool             = 1 ;
   languageOptions.CPlusPlus        = 1 ;
   languageOptions.WChar            = 1 ; // stdlib.h and friends want wchar_t to be defined by the compiler in C++ mode.
   //languageOptions.NoBuiltin        = 0 ;

   FileSystemOptions fileSystemOptions ;

   FileManager fileManager( fileSystemOptions ) ;

   SourceManager sourceManager( *pDiagnosticsEngine,
                                fileManager ) ;

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

   Preprocessor preprocessor( pOpts,
                              *pDiagnosticsEngine,
                              languageOptions,
                              pTargetInfo,
                              sourceManager,
                              headerSearch,
                              compInst ) ;

   FrontendOptions frontendOptions ;
   //frontendOptions.SkipFunctionBodies = 1 ;

   InitializePreprocessor( preprocessor,
                           *pOpts,
                           *headerSearchOptions,
                           frontendOptions ) ;

   const FileEntry * pFile = fileManager.getFile( argv[optind] ) ;
   
   if ( pFile )
   {
      sourceManager.createMainFileID( pFile ) ;

      Rewriter TheRewriter ;

      #if defined REWRITER
      // A Rewriter helps us manage the code rewriting task.
      TheRewriter.setSourceMgr( sourceManager, languageOptions ) ;
      #endif

      IdentifierTable identifierTable( languageOptions ) ;

      SelectorTable selectorTable ;

      Builtin::Context builtinContext ;

      builtinContext.InitializeTarget( *pTargetInfo ) ;
      //builtinContext.InitializeBuiltins( identifierTable, languageOptions ) ;

      ASTContext * pASTcontext = new ASTContext( languageOptions,
                                                 sourceManager,
                                                 pTargetInfo,
                                                 identifierTable,
                                                 selectorTable,
                                                 builtinContext,
                                                 0 /* size_reserve*/ ) ;

      compInst.setASTContext( pASTcontext ) ;

      MyASTConsumer astConsumer( compInst, TheRewriter ) ;

      pTextDiagnosticPrinter->BeginSourceFile( languageOptions, &preprocessor ) ;

      ParseAST( preprocessor, &astConsumer, *pASTcontext ) ;

      pTextDiagnosticPrinter->EndSourceFile() ;

      #if defined CLASSVISITOR
         g_depMap.dump() ;
      #endif

      #if defined REWRITER
         // At this point the rewriter's buffer should be full with the rewritten
         // file contents.
         const RewriteBuffer * RewriteBuf =
             TheRewriter.getRewriteBufferFor( sourceManager.getMainFileID() ) ;

         if ( RewriteBuf )
         {
            llvm::outs() << string( RewriteBuf->begin(), RewriteBuf->end() ) ;
         }
         else
         {
            cout << "file unchanged: " << argv[optind] << endl ;
         }
      #endif
   }

   return 0 ;
}
