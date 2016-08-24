#include <iostream>
#include "is.h"

int main()
{
//   int k = 3/2 ;
//   std::cout << k << '\n' ;

   for ( auto v : {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 16, 25 } )
   {
	   std::cout << "\\sqrt{" << v << "} = " << isqrt( v ) << '\n' ;
   }

   return 0 ;
}
