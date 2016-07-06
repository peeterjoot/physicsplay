#include <stdio.h>

// comment in the book that seems to imply <iterator> is required for begin() end() with builtin types, but
// I don't see that here.  What was that referring to?
int main()
{
   int x[]{ 1, 2,3,4} ;

   for ( auto v : x )
   {
      printf( "%d\n", v ) ;
   }

   return 0 ;
}
