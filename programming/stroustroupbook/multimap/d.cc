#include <unordered_map>
#include <string>
#include <iostream>

int main()
{
   std::unordered_multimap< int, std::string > m ;

   m.emplace( 3, "hi" ) ;
   m.emplace( 3, "bye" ) ;
   m.emplace( 4, "wow" ) ;

   for ( auto & v : m )
   {
      std::cout << v.first << ": " << v.second << '\n' ;
   }
  
   for ( auto f{ m.find(3) } ; f != m.end() ; ++f )
   {
      std::cout << "find: " << f->first << ": " << f->second << '\n' ;
   }
   
   return 0 ;
} 
