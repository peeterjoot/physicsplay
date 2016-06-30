#include "matrix.h"

void outofbounds( const matrix & m )
{
   printf( "%g\n", m(4,2) ) ;
}

void outofbounds( const uncheckedMatrix & m ) noexcept
{
   printf( "%g\n", m(4,2) ) ;
}
