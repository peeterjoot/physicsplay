#include <iostream>
#include <string>
#if 0
#include "boost/regex.hpp"
#else
#include <regex>
#endif

int main()
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
