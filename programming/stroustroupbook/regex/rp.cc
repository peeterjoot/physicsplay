#include "posix_regex.h"

using namespace posixhelper ;

void fail()
try {
   // https://github.com/agordon/posix-libc-examples/blob/master/regex-examples.c : a bad regex:
   regex re( "hello([0-9*world" ) ;
}
catch ( std::exception & e )
{
   std::cerr << "fail: error: " << e.what() << '\n' ;
}

int main()
try {
   //regex re( R"(\q\a\x\y\e\f\g)" ) ;
#if 0
   // works on Linux, but not on Mac:
   regex re( R"((\S+)(\s+)(\S+))" ) ;
#else
   regex re( R"(([^[:space:]]+)([[:blank:]]+)([^[:space:]]+))" ) ;
#endif
   //regex re( "\\S+\\s\\S+" ) ;
   //regex re( "[^[:space:]]+[[:space:]][^[:space]]+" ) ;
   //regex re( "[[:space:]]+[[:space:]][[:space]]+" ) ;
   //regex re( "[:space:]+x[:space]+" ) ;
   //regex re( "[:space:]+x[:space]+" ) ;

   fail() ;

   const char * pat { "blah rah" } ;
   if ( re.exec( pat ) )
   {
      std::cout << "match: " << pat << '\n' ;
   }
   else
   {
      std::cout << "no match: '" << pat << "'\n" ;
   }

   regex::regmatch< 4 > m{ pat } ;
   if ( re.exec( m ) )
   {
      std::cout << "match: " << pat << '\n' ;

      std::cout << "match data\n" ;
      for ( size_t i{} ; i < m.m_matchResults.size() ; i++ )
      {
         std::cout << i << " : " << m[i] << '\n' ;
      }

      std::cout << pat << " -> " << m[3] << " " << m[1] << '\n' ;
   }
   else
   {
      std::cout << "no match: '" << pat << "'\n" ;
   }

   //const char * pat2 { "blahblah" } ;
   const char * pat2 { "   x   " } ;
   if ( re.exec( pat2 ) )
   {
      std::cout << "match: " << pat2 << '\n' ;
   }
   else
   {
      std::cout << "no match: '" << pat2 << "'\n" ;
   }

   return 0 ;
}
catch ( std::exception & e )
{
   std::cerr << "error: " << e.what() << '\n' ;

   return 1 ;
}
