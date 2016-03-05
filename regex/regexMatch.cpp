#include <iostream>
#include <string>
//#include "boost/regex.hpp"
#include <regex>

int main()
{
   std::string s{ "foo.rat" } ;
   std::regex reg{ R"((.*)\.rat$)" } ;

   s = std::regex_replace( s, reg, "$1.csv" ) ;

   std::cout << s << std::endl ;

   s = std::regex_replace( "foo.noo", reg, "$1.csv" ) ;
   std::cout << s << std::endl ;

   return 0 ;
}


int xmain()
{
   std::string s { "a b" } ;

#if 0
   boost::regex reg( "(.*) (.*)", boost::regex::perl ) ;

   s = boost::regex_replace( s, reg, "$2 $1" ) ;
#else
   std::regex reg{ "(.*) (.*)" } ;

   s = std::regex_replace( s, reg, "$2 $1" ) ;
#endif

   std::cout << s << std::endl ;

   return 0 ;
}
