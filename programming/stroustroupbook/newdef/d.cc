#include <stdio.h>

int main()
{
   double * d1 = new double ;    
   double * d2 = new double{} ;

   printf( "%g %g\n", *d1, *d2 ) ;

   return 0 ;
}
