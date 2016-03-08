#include "rarray"
#include <iostream>

using namespace std ;

int main()
{
   rarray<int, 1> a(3) ;

   a[0] = 0 ;
   a[1] = 1 ;
   a[2] = 2 ;

   for ( auto e : a )
   {
      cout << e << endl ;
   }

   return 0 ;
}
