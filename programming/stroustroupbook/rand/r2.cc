#include <random>
#include <functional>
#include <iostream>
#include <unordered_map>

using namespace std ;

// an exact copy of the class in Stroustrup chapter 40.  does not compile.
class Rand_int
{  
public:
   Rand_int( int lo, int hi ) : p{ lo, hi } {  }
   int operator()() const { return r() ; }
private:
   uniform_int_distribution<>::param_type  p ;
   auto r = bind( uniform_int_distribution<>{ p }, default_random_engine{} ) ;
} ;

int main()
{
   unordered_map<int, int> buckets ;
   Rand_int r( -3, 6 ) ;

   cout << "Value\n" ;
   for ( int i{} ; i < 10000 ; i++ )
   {
      buckets[ r() ]++ ;
   }

   for ( auto v : buckets )
   {
      cout << v.first << ", " << v.second << '\n' ;
   }

   return 0 ;
}
