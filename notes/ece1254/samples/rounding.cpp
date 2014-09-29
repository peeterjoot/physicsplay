#define __STDC_FORMAT_MACROS
#include <stdio.h>
#include <math.h>
#include <inttypes.h>

struct doubleRepresentation
{
   uint64_t s : 1 ;
   uint64_t e : 11 ;
   uint64_t m : 52 ;
} ;

union doubleU
{
   double d ;
   doubleRepresentation r ;
} ;

int main()
{
   doubleU d1 ;
   doubleU d2 ;

   d1.d = (1 + M_PI * 1e-17) - 1 ;
   d2.d = M_PI * 1e-17 ;

   printf( "%g: %" PRIx64 ":%" PRIx64 ":%" PRIx64 "\n", d1.d, d1.r.s, d1.r.e, d1.r.m ) ;
   printf( "%g: %" PRIx64 ":%" PRIx64 ":%" PRIx64 "\n", d2.d, d2.r.s, d2.r.e, d2.r.m ) ;

   return 0 ;
}
