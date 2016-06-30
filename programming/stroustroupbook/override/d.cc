#include <stdio.h>
#include "matrix.h"

void outofbounds( const matrix & m ) ;

void outofbounds( const uncheckedMatrix & m ) noexcept ;

int main()
try {
   matrix m1{ 1., 2., 3. } ;
   uncheckedMatrix m2{ 1., 2., 3. } ;

   outofbounds( m2 ) ;
   outofbounds( m1 ) ;

   return 0 ;
}
catch ( matrix::rangeError & e )
{
   printf( "range error: i,j = %lu, %lu\n", e.i, e.j ) ;

   return 1 ;
}
