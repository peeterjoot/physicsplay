#include <iostream>
#include <string>
//#include "boost/regex.hpp"
#include <regex>

int main()
{
   std::string s{ "foo.rat" } ;
   std::regex reg{ R"((.*)\.rat$)" } ;

   std::smatch m ;
   if ( std::regex_match( s, m, reg ) )
   {
      std::cout << m.str() << std::endl ;
      for ( auto sm : m )
      {
         std::cout << sm.str() << std::endl ;
      }
      
      
      std::cout << "r: " << m[1].str() + ".csv" << std::endl ;
   }
   else
   {
      std::cout << "no match for " << s << std::endl ;
   }

   s = "foo.goo" ;

   if ( std::regex_match( s, m, reg ) )
   {
      std::cout << m.str() << std::endl ;
   }
   else
   {
      std::cout << "no match for " << s << std::endl ;
   }

   return 0 ;
}

int ymain()
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
