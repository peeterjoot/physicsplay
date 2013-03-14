#include <set>
#include <fstream>

class dependencyMap
{
   typedef set< string >              stringSet ;
   typedef map< string, stringSet >   dependencyContainerType ;

   dependencyContainerType m_typeDeps ;

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

   /**
      dump the dependency tree.
    */
   void dumpOne( const string t, stringSet & seen, const string & indent )
   {
      g_out << indent << t << " : " << endl ;
      const string moreindent = indent + "   " ;

      for ( auto & v : m_typeDeps[ t ] )
      {
         if ( v == g_typeSuppressed )
         {
         }
         else if ( seen.count( v ) )
         {
            g_out << moreindent << v << endl ;
         }
         else
         {
            seen.insert( v ) ;

            dumpOne( v, seen, moreindent ) ;
         }
      }
   }

public:
   /**
      A pair of types.  The type and something that it depends on.
    */
   void insertDependency( const string & theTypeName, const string & theTypeDep )
   {
      m_typeDeps[ theTypeName ].insert( theTypeDep ) ;
   }

   /**
      dump dependencies as a tree.
    */
   void dump( )
   {
      ifstream file ; // Will let destructor cleanup ifstream object.

      if ( g_symbolfile )
      {
         file.open( g_symbolfile ) ;

         if ( file.is_open() )
         {
            string line ;

            while ( file >> line )
            {
               stringSet seen ;

               dumpOne( line, seen, "" ) ;
            }
         }
         else
         {
            cout << "Failed to process --symbolfile==" << g_symbolfile << endl ;
         }
      }
      else
      {
         /* didn't find a list of specific symbols of interest.  Dump all symbols */
         for ( auto & k : m_typeDeps )
         {
            stringSet seen ;

            dumpOne( k.first, seen, "" ) ;
         }
      }
   }

   /**
      Find all the dependencies of a type recursively and dump them for each type in flat fashion.
    */
   void dumpRecursiveDeps( )
   {
      for ( auto & k : m_typeDeps )
      {
         g_out << k.first << " : " ;

         stringSet s ;

         collectAllDeps( s, k.first ) ;

         const char * commaOrBlank = "" ;

         for ( auto & v : s )
         {
            if ( g_typeSuppressed != v )
            {
               g_out << commaOrBlank << v ;

               commaOrBlank = ", " ;
            }
         }

         g_out << endl ;
      }
   }

   void dumpJustDeps( )
   {
      for ( auto & k : m_typeDeps )
      {
         for ( auto & v : m_typeDeps[ k.first ] )
         {
            g_out << v << endl ;
         }
      }
   }

   void dumpDirectDeps()
   {
      for ( auto & k : m_typeDeps )
      {
         g_out << k.first << " : " ;

         const char * commaOrBlank = "" ;

         for ( auto & v : m_typeDeps[ k.first ] )
         {
            g_out << commaOrBlank << v ;

            commaOrBlank = ", " ;
         }

         g_out << endl ;
      }
   }
} g_depMap ;

bool g_quietDeps = true ;
