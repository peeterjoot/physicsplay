#include <stdio.h>
#include "matrix.h"

/** Implicitly checked with vft cost to doing so. */
void outofbounds( const matrix & m, const char * s ) ;

/** Explicitly checked without vft cost to doing so. */
void outofbounds( const checkedMatrix & m, const char * s ) ;

/** unchecked.  Don't want vft cost, but have it. */
void outofbounds( const uncheckedMatrix & m, const char * s ) noexcept ;

/** unchecked.  have to redefine element access operator to not have the cost. */
void outofbounds( const uncheckedMatrix2 & m, const char * s ) noexcept ;

int main()
{
   uncheckedMatrix2 m0{ 1., 2., 3. } ;

   outofbounds( m0, "m0" ) ;

   uncheckedMatrix m1{ 1., 2., 3. } ;

   outofbounds( m1, "m1" ) ;

   try {
      matrix m2{ 1., 2., 3. } ;

      outofbounds( m2, "m2" ) ;
   }
   catch ( matrix::rangeError & e )
   {
      printf( "m2: range error: i,j (sz) = %lu, %lu (%lu)\n", e.i, e.j, e.sz ) ;
   }

   try {
      checkedMatrix m3{ 1., 2., 3. } ;

      outofbounds( m3, "m3" ) ;
   }
   catch ( matrix::rangeError & e )
   {
      printf( "m3: range error: i,j (sz) = %lu, %lu (%lu)\n", e.i, e.j, e.sz ) ;
   }

   return 0 ;
}
