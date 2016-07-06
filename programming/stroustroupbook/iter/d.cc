#include <stdio.h>

// comment in the book that seems to imply <iterator> is required for begin() end() with builtin types?
int main()
{
   int x[]{ 1, 2,3,4} ;

   for ( auto v : x )
   {
      printf( "%d\n", v ) ;
   }

   return 0 ;
}
