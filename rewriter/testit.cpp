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

   void dump()
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
   d.insert( "Test", "int" ) ;

   d.dump() ;

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
