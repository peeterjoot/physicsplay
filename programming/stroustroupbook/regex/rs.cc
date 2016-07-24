#include <regex>
#include <iostream>
#include <exception>

int main()
try {
   std::regex r( "\\S+\\s+\\S+" ) ;

   std::smatch m ;

   if ( regex_match( std::string("hi bye"), m, r ) )
   {
      std::cout << "match: 'hi bye'\n" ;
   }

   if ( regex_match( std::string("hbye"), m, r ) )
   {
      std::cout << "match: 'hbye'\n" ;
   }

   return 0 ;
}
catch ( std::exception & e )
{
   std::cerr << "uncaught: " << e.what() << '\n' ;

   return 1 ;
}
