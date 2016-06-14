#include <stdio.h>

/****************************************************************************
 *
 * From A Leon-Garcia appendix C.
 *
 ***************************************************************************/
#include <math.h>

#define A 16807.0
#define M 2147483647.0
#define i_seed 1.0

class random
{ 
private:
   double r_seed ;
public:
   random() : r_seed( i_seed ) {}

   /** generates a uniform random variable (0, 1) */
   double rnd( )
   {
      r_seed = fmod( A * r_seed, M ) ;
      return r_seed * 4.656612875e-10 ;
   }

   /** generates a continuous uniform random variable (0, 1) */
   double unifc( double a, double b )
   {
      return ( a + ( b - a ) * rnd() ) ;      
   }
} ;
/****************************************************************************/

int main()
{
   random r ;
   printf( "%g\n", r.unifc( 1.0, 10.0 ) ) ;
   printf( "%g\n", r.unifc( 1.0, 10.0 ) ) ;
   printf( "%g\n", r.unifc( 1.0, 10.0 ) ) ;
   printf( "%g\n", r.unifc( 1.0, 10.0 ) ) ;
   printf( "%g\n", r.unifc( 1.0, 10.0 ) ) ;
   printf( "%g\n", r.unifc( 1.0, 10.0 ) ) ;
   printf( "%g\n", r.unifc( 1.0, 10.0 ) ) ;
   printf( "%g\n", r.unifc( 1.0, 10.0 ) ) ;
   printf( "%g\n", r.unifc( 1.0, 10.0 ) ) ;

   return 0 ;
}
