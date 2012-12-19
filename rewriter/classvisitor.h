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

using namespace clang ;
using namespace std ;

#if defined CLASSVISITOR
#include <set>

class dependencyMap
{
   typedef set< string >              stringSet ;
   typedef map< string, stringSet >   dependencyContainerType ;

   dependencyContainerType m_typeDeps ;

public:
   void insert( const string & theTypeName, const string & theTypeDep )
   {
      m_typeDeps[ theTypeName ].insert( theTypeDep ) ;
   }

   void collectAllDeps( stringSet & allDeps, const string & theTypeName )
   {
      auto & setOfDepsForThisType = m_typeDeps[ theTypeName ] ;

      for ( auto & oneDependentType : setOfDepsForThisType )
      {
         if ( m_typeDeps.count( oneDependentType ) )
         {
            collectAllDeps( allDeps, oneDependentType ) ;
         }
         else
         {
            allDeps.insert( setOfDepsForThisType.begin(), setOfDepsForThisType.end() ) ;
         }
      }
   }

   void dump( )
   {
      for ( auto & k : m_typeDeps )
      {
         cout << k.first << " : " ;

         stringSet s ;

         collectAllDeps( s, k.first ) ;

         const char * commaOrBlank = "" ;

         for ( auto & v : s )
         {
            cout << commaOrBlank << v ;

            commaOrBlank = ", " ;
         }

         cout << endl ;
      }
   }

   void dumpJustDeps( )
   {
      for ( auto & k : m_typeDeps )
      {
         for ( auto & v : m_typeDeps[ k.first ] )
         {
            cout << v << endl ;
         }
      }
   }

   void dumpNoDeps()
   {
      for ( auto & k : m_typeDeps )
      {
         cout << k.first << " : " ;

         const char * commaOrBlank = "" ;

         stringSet deps = m_typeDeps[ k.first ] ;

         for ( auto & v : deps )
         {
            cout << commaOrBlank << v ;

            commaOrBlank = ", " ;
         }

         cout << endl ;
      }
   }
} g_depMap ;
#endif

inline QualType getQualTypeForDecl( DeclaratorDecl * f )
{
   TypeSourceInfo * pThisFieldSourceInfo = f->getTypeSourceInfo() ;

   TypeLoc thisFieldTypeLoc = pThisFieldSourceInfo->getTypeLoc() ;

   // don't care if it's an array, just want the basic underlying type of the array.
   for ( ; ; )
   {
      if ( const ArrayTypeLoc * pTypeLocIfArray = dyn_cast<ArrayTypeLoc>( &thisFieldTypeLoc ) )
      {
         thisFieldTypeLoc = pTypeLocIfArray->getElementLoc() ;
      }
      else
      {
         break ;
      }
   } 

   return thisFieldTypeLoc.getType() ;
}

// By implementing RecursiveASTVisitor, we can specify which AST nodes
// we're interested in by overriding relevant methods.
class MyASTVisitor : public RecursiveASTVisitor<MyASTVisitor>
{
   CompilerInstance &            m_ci ;
   ASTContext &                  m_context ;
   PrintingPolicy                m_pp ;

public:
   MyASTVisitor( CompilerInstance & ci_ ) :
      m_ci( ci_ ),
      m_context( m_ci.getASTContext() ),
      m_pp( m_context.getLangOpts() )
   {
      m_pp.SuppressTagKeyword = 1 ;
   }

#if defined GLOBALVISITOR
   static string subMemberString( const string & prefix, const string & field )
   {
      string s = prefix ;

      if ( "" != prefix )
      {
         s += "." ;
      }

      s += field ;

      return s ;
   }

   // 
   // 1.  Look at the constructor: getConstructor().
   // 2.  Check whether it's a implicitly-defined default constructor: isDefaultConstructor(), isImplicitlyDefined().  If not, you've found your problem right there.
   // 3.  Iterate over the initializers: init_begin(), init_end().
   // 4.  I believe the expression for each initializer should always be a CXXConstructExpr.  Recurse.
   //
   void recurseOverConstructorDecls( CXXConstructorDecl * c, string subobject )
   {
      for ( CXXConstructorDecl::init_iterator b = c->init_begin(), e = c->init_end() ;
            b != e ; ++b )
      {
         CXXCtorInitializer *    i        = *b ;
         FieldDecl *             f        = i->getMember() ;
         Expr *                  Init     = i->getInit() ;
         string                  subfield = subMemberString( subobject, f->getName().str() ) ;

         const QualType &        ftype    = getQualTypeForDecl( f ) ; // type of the field.  Now check if that type has a constructor.

         if ( const CXXConstructExpr * r = dyn_cast<CXXConstructExpr>( Init ) )
         {
            CXXConstructorDecl * cInner   = r->getConstructor() ;
            CXXRecordDecl *      frec     = ftype->getAsCXXRecordDecl() ;

#if 0
            if ( frec->hasDefaultConstructor() ) { cout << frec->getName().str() << " : CONSTRUCTOR: hasDefaultConstructor" << endl ; }
            if ( frec->hasConstCopyConstructor() ) { cout << frec->getName().str() << " : CONSTRUCTOR: hasConstCopyConstructor" << endl ; }
            if ( frec->hasUserDeclaredConstructor() ) { cout << frec->getName().str() << " : CONSTRUCTOR: hasUserDeclaredConstructor" << endl ; }
            if ( frec->hasUserProvidedDefaultConstructor() ) { cout << frec->getName().str() << " : CONSTRUCTOR: hasUserProvidedDefaultConstructor" << endl ; }
            if ( frec->hasUserDeclaredCopyConstructor() ) { cout << frec->getName().str() << " : CONSTRUCTOR: hasUserDeclaredCopyConstructor" << endl ; }
            if ( frec->hasCopyConstructorWithConstParam() ) { cout << frec->getName().str() << " : CONSTRUCTOR: hasCopyConstructorWithConstParam" << endl ; }
            if ( frec->hasMoveConstructor() ) { cout << frec->getName().str() << " : CONSTRUCTOR: hasMoveConstructor" << endl ; }
            if ( frec->hasTrivialDefaultConstructor() ) { cout << frec->getName().str() << " : CONSTRUCTOR: hasTrivialDefaultConstructor" << endl ; }
            if ( frec->hasNonTrivialDefaultConstructor() ) { cout << frec->getName().str() << " : CONSTRUCTOR: hasNonTrivialDefaultConstructor" << endl ; }
            if ( frec->hasConstexprDefaultConstructor() ) { cout << frec->getName().str() << " : CONSTRUCTOR: hasConstexprDefaultConstructor" << endl ; }
            if ( frec->hasTrivialCopyConstructor() ) { cout << frec->getName().str() << " : CONSTRUCTOR: hasTrivialCopyConstructor" << endl ; }
            if ( frec->hasNonTrivialCopyConstructor() ) { cout << frec->getName().str() << " : CONSTRUCTOR: hasNonTrivialCopyConstructor" << endl ; }
            if ( frec->hasUserDeclaredMoveConstructor() ) { cout << frec->getName().str() << " : CONSTRUCTOR: hasUserDeclaredMoveConstructor" << endl ; }
            if ( frec->hasFailedImplicitMoveConstructor() ) { cout << frec->getName().str() << " : CONSTRUCTOR: hasFailedImplicitMoveConstructor" << endl ; }
            if ( frec->hasConstexprNonCopyMoveConstructor() ) { cout << frec->getName().str() << " : CONSTRUCTOR: hasConstexprNonCopyMoveConstructor" << endl ; }
            if ( frec->hasTrivialMoveConstructor() ) { cout << frec->getName().str() << " : CONSTRUCTOR: hasTrivialMoveConstructor" << endl ; }
            if ( frec->hasNonTrivialMoveConstructor() ) { cout << frec->getName().str() << " : CONSTRUCTOR: hasNonTrivialMoveConstructor" << endl ; }
#endif

            if ( !cInner->isImplicitlyDefined() &&
                 ( frec->hasUserDeclaredConstructor() ||
                   frec->hasUserProvidedDefaultConstructor() ||
                   frec->hasUserDeclaredCopyConstructor() ||
                   frec->hasNonTrivialDefaultConstructor() ||
                   frec->hasConstexprDefaultConstructor() ||
                   frec->hasNonTrivialCopyConstructor() ||
                   frec->hasUserDeclaredMoveConstructor()  ||
                   frec->hasFailedImplicitMoveConstructor()  ||
                   frec->hasConstexprNonCopyMoveConstructor()  ||
                   frec->hasNonTrivialMoveConstructor()  ||
                   //frec->hasConstCopyConstructor() ||
                   //frec->hasTrivialMoveConstructor()  ||
                   //frec->hasDefaultConstructor() ||
                   //frec->hasCopyConstructorWithConstParam() ||
                   //frec->hasMoveConstructor() ||
                   //frec->hasTrivialDefaultConstructor() ||
                   //frec->hasTrivialCopyConstructor() ||
                   0 )
               )
            {
               cout 
                  << "Global subobject requires constructor: " 
                  << subfield 
                  << " : " 
                  << ftype.getAsString() 
                  << endl ;

               recurseOverConstructorDecls( cInner, subfield ) ;
            }
         }
      }
   }

   bool VisitVarDecl( VarDecl * var )
   {
      // modified from Eli's email "Here's the code used to implement -Wglobal-constructor:"
      Expr *         Init     = var->getInit() ;
      bool           IsGlobal = var->hasGlobalStorage() && !var->isStaticLocal() ;
      QualType       type     = var->getType();
      QualType       baseType = m_context.getBaseElementType( type ) ;

      if ( !var->getDeclContext()->isDependentContext() && Init && !Init->isValueDependent() )
      {
         if ( IsGlobal && !var->isConstexpr() &&
              !Init->isConstantInitializer( m_context, baseType->isReferenceType() ) )
         {
            if ( const CXXConstructExpr * r = dyn_cast<CXXConstructExpr>( Init ) )
            {
               CXXConstructorDecl * c = r->getConstructor() ;

               recurseOverConstructorDecls( c, var->getName().str() ) ;
            }
         }
      }

      return true ;
   }
#endif

#if defined CLASSVISITOR

   void insertIntoMap( const string & theTypeName, const QualType & q, const string * const pAsString = NULL )
   {
#if 1
      const Type * t = q.getTypePtr() ;

      if ( t->isArithmeticType() ||
           t->isPointerType() ||
           t->isReferenceType() ||
           0 )
      {
         // skip these.
      }
      else 
#endif
         if ( pAsString )
      {
         g_depMap.insert( theTypeName, *pAsString ) ;
      }
      else
      {
         g_depMap.insert( theTypeName, q.getAsString( m_pp ) ) ;
      }
   }

   // Find typedefs:
   bool VisitTypedefDecl( TypedefDecl * dtDecl )
   {
      const QualType &  qtUnderLying         = dtDecl->getUnderlyingType() ;
      const Type *      tUnderlying          = qtUnderLying.getTypePtr() ;
      string            theUnderlyingType    = qtUnderLying.getAsString( ) ;
      string            typeDefinitionName   = dtDecl->getName().str() ;
      string *          pName                = NULL ;

#if 0
      if ( const RecordType * r = dyn_cast<RecordType>( tUnderlying ) )
      {
cout << "RecordType: " << typeDefinitionName << ","<< theUnderlyingType << ":" << r->getDecl()->getName().str() << endl ;
#if 0
         theUnderlyingType = r->getDecl()->getName().str() ;
         pName = &theUnderlyingType ;
#endif
      }
#endif

      if ( tUnderlying->isStructureType() )
      {
         theUnderlyingType = theUnderlyingType.substr(strlen("struct ")) ;
         pName = &theUnderlyingType ;
      }
      else if ( tUnderlying->isClassType() )
      {
         theUnderlyingType = theUnderlyingType.substr(strlen("class ")) ;
         pName = &theUnderlyingType ;
      }
      else if ( tUnderlying->isUnionType() )
      {
         theUnderlyingType = theUnderlyingType.substr(strlen("union ")) ;
         pName = &theUnderlyingType ;
      }

      if ( typeDefinitionName != theUnderlyingType )
      {
         insertIntoMap( typeDefinitionName, qtUnderLying, pName ) ;
      }

      return true ;
   }

   // Find class/struct/unions:
   bool VisitCXXRecordDecl( CXXRecordDecl * r )
   {
      if ( r->isThisDeclarationADefinition() )
      {
         for ( CXXRecordDecl::base_class_iterator b = r->bases_begin(), e = r->bases_end() ;
               b != e ; ++b )
         {
            CXXBaseSpecifier & a = *b ;

            const QualType & q = a.getType() ;

            insertIntoMap( r->getName().str(), q ) ;
         }
      }

      return true ;
   }

   // Member's within class/struct/union:
   bool VisitFieldDecl( FieldDecl * f )
   {
      RecordDecl * r = f->getParent() ;
      const QualType & theMembersClassType = m_context.getRecordType( r ) ;
      const QualType & thisFieldQualType = getQualTypeForDecl( f ).getDesugaredType( m_context ) ;

      insertIntoMap( theMembersClassType.getAsString( m_pp ), thisFieldQualType ) ;

      return true ;
   }
#endif
} ;

// Implementation of the ASTConsumer interface for reading an AST produced
// by the Clang parser.
class MyASTConsumer : public ASTConsumer
{
public:
   MyASTConsumer( CompilerInstance & ci_ ) : Visitor( ci_ ) {}

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

int main( int argc, char * argv[] )
{
   struct option options[] =
   {
       {"include", 1, 0, 'I'}
      ,{"define", 1, 0, 'D'}
      ,{"undef", 1, 0, 'U'}
      ,{"help", 1, 0, 'h'}
   } ;

   int c = 0 ;
   int optindex = 0 ;

   llvm::IntrusiveRefCntPtr<PreprocessorOptions> pOpts( new PreprocessorOptions() ) ;
   llvm::IntrusiveRefCntPtr<HeaderSearchOptions> headerSearchOptions( new HeaderSearchOptions() ) ;

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
                       "O:" // -O2 -O0 ...
                       "m:" // -msse4.2 ...
                       "f:" // -fcheck-new ...
                       "g"  // -g
                       "",
                       options,
                       &optindex ) ;
            /* dummy args: */ 

      switch (c)
      {
         case 'W':
         case 'c':
         case 'O':
         case 'm':
         case 'f':
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
                                          true,
                                          false,
                                          false ) ;

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
   languageOptions.GNUMode = 1 ;
   languageOptions.CXXExceptions = 1 ;
   languageOptions.RTTI = 1 ;
   languageOptions.Bool = 1 ;
   languageOptions.CPlusPlus = 1 ;

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

      IdentifierTable identifierTable( languageOptions ) ;

      SelectorTable selectorTable ;

      Builtin::Context builtinContext ;

      builtinContext.InitializeTarget( *pTargetInfo ) ;

      ASTContext * pASTcontext = new ASTContext( languageOptions,
                                                 sourceManager,
                                                 pTargetInfo,
                                                 identifierTable,
                                                 selectorTable,
                                                 builtinContext,
                                                 0 /* size_reserve*/ ) ;

      compInst.setASTContext( pASTcontext ) ;

      MyASTConsumer astConsumer( compInst ) ;

      pTextDiagnosticPrinter->BeginSourceFile( languageOptions, &preprocessor ) ;

      ParseAST( preprocessor, &astConsumer, *pASTcontext ) ;

      pTextDiagnosticPrinter->EndSourceFile() ;

      #if defined CLASSVISITOR
         g_depMap.dump() ;
      #endif
   }

   return 0 ;
}
