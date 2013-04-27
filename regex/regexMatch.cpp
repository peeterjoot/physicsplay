#include <iostream>
#include <string>
#include "boost/regex.hpp"

int main()
{
   boost::regex reg( "(.*) (.*)", boost::regiex::perl ) ;

   std::string s = "a b" ;

   s = boost::regex_replace( s, reg, "$2$1" ) ;

   std::cout << s << endl ;

   return 0 ;
}
