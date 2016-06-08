#include <stdio.h>
#include "foo.h"

void bar( void ) ;

int foo( void ) NOEXCEPT
{
   int rc = 0 ;
   try {
      //
   }
   catch ( ... )
   {
      // handle error
      rc = 1 ;
   }

   bar() ;

   return rc ;
}

void bar( void )
{
   throw 1 ;
}

int main()
{
   int v = foo() ;

   printf( "%d\n", v ) ;

   return 0 ;
}
