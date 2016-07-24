#include <regex>
#include <iostream>
#include <exception>

int main()
try {
   //std::regex r( "(\\S+)\\s+(\\S+)" ) ;
   std::regex r( R"((\S+)(\s+)(\S+))" ) ;

   std::string p[]{ "hi bye", "hbye" } ;

   for ( auto s : p )
   {
      std::smatch m ;

      if ( regex_match( s, m, r ) )
      {
         std::cout << "match: '" << s << "' -> '" << m[3] << ' ' << m[1] << "'\n" ;

         for ( auto r : m )
         {
            std::cout << "m: '" << r << "'\n" ;
         }
      }
      else
      {
         std::cout << "no match: '" << s << "'\n" ;
      }

      // string compare appears to be the only way to check for success:
      auto replace = regex_replace( s, r, R"($3 $1)" ) ;
      if ( replace != s )
      {
         std::cout << "replace: " << replace << '\n' ;
      }
   }

   return 0 ;
}
catch ( std::exception & e )
{
   std::cerr << "uncaught: " << e.what() << '\n' ;

   return 1 ;
}
