#include <iostream>
#include <string>
#include <regex>

using namespace std ;

int main()
{
   // This should match any word
   regex word("[[:alpha:]]+");
   string input = "hi 7 bye" ;

   // Replace with an empty string
   const string format = "" ;

   string clean_words = regex_replace( input, word, format, regex_constants::format_default ) ;
   cout << clean_words << endl ;

   return 0 ;
}

#if 0
int main()
{
   regex tag( "(class )" ) ;
   const string format = "" ;
   const string input = "class foo" ;

//   regex_constants::ECMAScript
   string r = regex_replace( input, tag, format, regex_constants::format_no_copy | regex_constants::ECMAScript) ;
   cout << input << " -> " << r << endl ;

   r = regex_replace( input, tag, format ) ;
   cout << input << " -> " << r << endl ;

   return 0 ;
}
#elif 0
int main()
{
   //regex tag( "^(class|struct|union) ") ; 
   regex tag( "class " ) ;

   const string inputs[] = 
   {
      "struct foo",
      "class foo",
      " class foo",
      "union foo",
   } ;

   const string format = "" ;


   return 0 ;
}
#elif 0
int main()
{
   //regex tag( "^(class|struct|union) ") ; 
   regex tag( "class " ) ;

   const string inputs[] = 
   {
      "struct foo",
      "class foo",
      " class foo",
      "union foo",
   } ;

   const string format = "" ;

   for ( auto & v : inputs )
   {
      string r = regex_replace( v, tag, format, regex_constants::format_default ) ;

      cout << v << " -> " << r << endl ;
   }

   return 0 ;
}
#endif

#if 0
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
#endif

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
