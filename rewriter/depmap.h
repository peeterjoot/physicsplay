#include <set>
string g_typeSuppressed( "<>" ) ;

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

public:
   /**
      A pair of types.  The type and something that it depends on.
    */
   void insertDependency( const string & theTypeName, const string & theTypeDep )
   {
      m_typeDeps[ theTypeName ].insert( theTypeDep ) ;
   }

   /**
      dump the dependency tree.
    */
   void dumpOne( const string t, stringSet & seen, const string & indent )
   {
      cout << indent << t << " : " << endl ;
      const string moreindent = indent + "   " ;

      for ( auto & v : m_typeDeps[ t ] )
      {
         if ( v == g_typeSuppressed )
         {
         }
         else if ( seen.count( v ) )
         {
            cout << moreindent << v << endl ;
         }
         else
         {
            seen.insert( v ) ;

            dumpOne( v, seen, moreindent ) ;
         }
      }
   }

   /**
      dump dependencies as a tree.
    */
   void dump( )
   {
      for ( auto & k : m_typeDeps )
      {
         stringSet seen ;

         dumpOne( k.first, seen, "" ) ;
      }
   }

#if 0
   /**
      Find all the dependencies of a type recursively and dump them for each type in flat fashion.
    */
   void dumpflat( )
   {
      for ( auto & k : m_typeDeps )
      {
         cout << k.first << " : " ;

         stringSet s ;

         collectAllDeps( s, k.first ) ;

         const char * commaOrBlank = "" ;

         for ( auto & v : s )
         {
            if ( g_typeSuppressed != v )
            {
               cout << commaOrBlank << v ;

               commaOrBlank = ", " ;
            }
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

         for ( auto & v : m_typeDeps[ k.first ] )
         {
            cout << commaOrBlank << v ;

            commaOrBlank = ", " ;
         }

         cout << endl ;
      }
   }
#endif
} g_depMap ;

bool g_quietDeps = true ;
