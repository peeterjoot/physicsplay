//
// This demonstrates that g++/libstdc++ is broken on 4.8.5, apparently fixed in 4.9.0:
//
//    http://stackoverflow.com/questions/14776605/c-11-regex-error
//

#include <iostream>
#include <string>
#include <regex>

using regex = std::regex ;
using smatch = std::smatch ;

int main()
try {
   std::string tests[] { "0", "+0", "-1", "a", "c" } ;
   regex reg{ R"(^[\+-]?\d+)" } ;

   for ( const auto & s : tests )
   {
      smatch m ;

      if ( regex_match( s, m, reg ) )
      {
         std::cout << m.str() << std::endl ;
         for ( auto sm : m )
         {
            std::cout << "smatch: " << sm.str() << std::endl ;
         }

         std::cout << "r: " << m[1].str() + ".csv" << std::endl ;
      }
      else
      {
         std::cout << "no match for: " << s << std::endl ;
      }
   }

   return 0 ;
}
catch ( const std::regex_error & e )
{
   std::cout << e.code() << '\n' ;
   std::cout << std::regex_constants::error_brack << '\n' ;

   return -1 ;
}
