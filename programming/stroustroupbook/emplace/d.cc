#include <vector>
#include <iostream>

int main()
{
   using pair = std::pair<int, int> ;
   using vector = std::vector< pair > ;

   vector v ;

   pair p{ 1, 2 } ;
   v.push_back( p ) ;
   v.push_back( {2, 3} ) ;
   v.emplace_back( 3, 4 ) ;

   for ( auto e : v )
   {
      std::cout << e.first << ", " << e.second << '\n' ;
   }

   return 0 ;
}
