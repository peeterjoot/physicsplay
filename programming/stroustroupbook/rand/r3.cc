#include <random>
#include <functional>
#include <iostream>
#include <unordered_map>

int main( int argc, char ** argv )
{
   std::random_device                  dev{} ;
   std::uniform_int_distribution<int>  uni{ 1, 5 } ;
   std::unordered_map<int, int>        buckets ;
   auto                                e = (argc == 1) ? std::mt19937() : std::mt19937{ dev() } ;
   auto                                u = std::bind( uni, e ) ;

   for ( int i{} ; i < 10000 ; i++ )
   {
      //buckets[ uni( e ) ]++ ;
      buckets[ u() ]++ ;
   }

   for ( auto v : buckets )
   {
      std::cout << v.first << ", " << v.second << '\n' ;
   }

   return 0 ;
}
