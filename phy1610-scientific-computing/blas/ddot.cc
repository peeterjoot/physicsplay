#include <iostream>
#include <cblas.h>

using namespace std ;

int main(int argc, char **argv)
{
   double x[] { 1.0, 2.0, 3.0 } ;
   double y[] { 1.0, 2.0, 3.0 } ;

   // double cblas_ddot(const int N, const double *X, const int incX, const double *Y, const int incY);
   auto dot { cblas_ddot( 3, x, 1, y, 1 ) } ;

   for ( auto e : x )
      cout << " " << e ;
   cout << endl ;

   for ( auto e : y )
      cout << " " << e ;
   cout << endl ;

   cout << dot << endl ;

   return 0 ;
}
