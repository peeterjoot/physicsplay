#include <iostream>
#include <string>
#if 1
   #include <boost/regex.hpp>

   using regex = boost::regex ;
   using smatch = boost::smatch ;
   //using regex_replace = boost::regex_replace ;
#else
   #include <regex>

   using regex = std::regex ;
   using smatch = std::smatch ;
   //using regex_replace = std::regex_replace ;
#endif

int main()
{
   std::string s{ "foo.rat" } ;
   regex reg{ R"((.*)\.rat$)" } ;

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
      std::cout << "no match for " << s << std::endl ;
   }

   s = "foo.goo" ;

   if ( regex_match( s, m, reg ) )
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
   regex reg{ R"((.*)\.rat$)" } ;

   s = regex_replace( s, reg, "$1.csv" ) ;

   std::cout << s << std::endl ;

   s = regex_replace( "foo.noo", reg, "$1.csv" ) ;
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
   regex reg{ "(.*) (.*)" } ;

   s = regex_replace( s, reg, "$2 $1" ) ;
#endif

   std::cout << s << std::endl ;

   return 0 ;
}
