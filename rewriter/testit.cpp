#include <map>
#include <set>
#include <string>
#include <iostream>

using namespace std ;

class dependencyMap
{
   typedef map< string, set< string > > dependencyContainerType ;

   dependencyContainerType m_typeDeps ;

public:
   void insert( const string & theTypeName, const string & theTypeDep )
   {
      m_typeDeps[ theTypeName ].insert( theTypeDep ) ;
   }

   void collectAllDeps( set< string > & allDeps, const string & theTypeName )
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

   void dump()
   {
      for ( auto & k : m_typeDeps )
      {
         cout << k.first << " : " ;

         set< string > s ;

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

   void dumpNoDeps()
   {
      for ( auto & k : m_typeDeps )
      {
         cout << k.first << " : " ;

         const char * commaOrBlank = "" ;

         set< string > deps = m_typeDeps[ k.first ] ;

         for ( auto & v : deps )
         {
            cout << commaOrBlank << v ;

            commaOrBlank = ", " ;
         }

         cout << endl ;
      }
   }
} ;

int main()
{
   dependencyMap d ;

   d.insert( "uu", "long" ) ;
   d.insert( "uu", "long" ) ;
   d.insert( "uu", "long long" ) ;

   d.insert( "qq", "int" ) ;
   d.insert( "qq", "uu" ) ;
   d.insert( "qq", "Test" ) ;
   d.insert( "Test", "int" ) ;
   d.insert( "Test", "uu" ) ;

   cout << "recursive:" << endl ;
   d.dump() ;

   cout << "flat:" << endl ;
   d.dumpNoDeps() ;

   return 0 ;
}

#if 0
void foo()
{
   typedef multimap< string, string > dependencyMap ;
   dependencyMap    m_typeDeps ;

   m_typeDeps.insert( dependencyMap::value_type( "uu", "long" ) ) ;
   m_typeDeps.insert( dependencyMap::value_type( "uu", "long" ) ) ;
   m_typeDeps.insert( dependencyMap::value_type( "uu", "long long" ) ) ;

   m_typeDeps.insert( dependencyMap::value_type( "qq", "int" ) ) ;
   m_typeDeps.insert( dependencyMap::value_type( "Test", "int" ) ) ;

   for ( auto & kv : m_typeDeps )
   {
      cout << kv.first << " : " << kv.second << endl ;
   }
}
#endif

#if 0
int main()
{
   set< string > d ;

   d.insert( "uu:long" ) ;
   d.insert( "uu:long" ) ;
   d.insert( "uu:long long" ) ;

   d.insert( "qq:int" ) ;
   d.insert( "Test:int" ) ;

   for ( auto & kv : d )
   {
      cout << kv << endl ;
   }
}
#endif
