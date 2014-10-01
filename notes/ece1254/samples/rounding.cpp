#define __STDC_FORMAT_MACROS
#include <stdio.h>
#include <math.h>
#include <inttypes.h>

// The ENDIAN macros here assume that the compiler is GCC
struct doubleRepresentation
{
#if defined __LITTLE_ENDIAN
   uint64_t m : 52 ;
   uint64_t e : 11 ;
   uint64_t s : 1 ;
#elif defined __BIG_ENDIAN
   uint64_t m : 52 ;
   uint64_t e : 11 ;
   uint64_t s : 1 ;
#else
   #error unknown endian
#endif
} ;

union doubleU
{
   double               d ;
   uint64_t             u ;
   doubleRepresentation r ;
} ;

void printDoubleRep( const double d )
{
   doubleU un ;
   un.d = d ;

   if ( un.u )
   {
      printf( "%g: %s1.0x%" PRIx64" x 2^%" PRId64 "\n", un.d, un.r.s ? "-" : "", un.r.m, (int64_t)un.r.e - 0x3ff ) ;
   }
   else
   {
      printf( "%g: 0\n", un.d ) ;
   }
}

int main()
{
   double d1 = (1 + M_PI * 1e-17) - 1 ;
   double d2 = M_PI * 1e-17 ;

   printDoubleRep( d1 ) ;
   printDoubleRep( d2 ) ;
   printDoubleRep( 1e-16 ) ;
   printDoubleRep( 1e-15 ) ;
//   printDoubleRep( 3 ) ;
//   printDoubleRep( 1 ) ;
//   printDoubleRep( -1 ) ;
//   printDoubleRep( -0.5 ) ;

   return 0 ;
}
