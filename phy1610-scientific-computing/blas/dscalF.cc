#include <iostream>
#include <cblas.h>

int main(int argc, char **argv)
{
   double x[] = { 1.0, 2.0, 3.0 } ;
   double coeff = 4.323 ;
   int one = 1 ;
   int n = 3 ;

   //Direct Fortran call
   dscal(&n, &coeff, &x[0], &one) ;

   for ( int i = 0 ; i < n ; i++ )
      std::cout << " " << x[i] ;

   return 0 ;
}
