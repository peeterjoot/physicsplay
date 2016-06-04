#include <iostream>

// Stroustrop 10.4:  constexpr capable integer square root function
constexpr int f( int s, int d, int a )
{
	return s <= a ? f( s + d, d + 2, a ) : d ;
}

constexpr int isqrt( int x )
{
	return f( 1, 3, x)/2 - 1 ;
}

int main()
{
   for ( auto v : {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 16, 25 } )
   {
	   std::cout << "\\sqrt{" << v << "} = " << isqrt( v ) << '\n' ;
   }

   return 0 ;
}
