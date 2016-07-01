#include "matrix.h"

void outofbounds( const matrix & m, const char * s )
{
   printf( "%s: %g\n", s, m(4,2) ) ;
}

void outofbounds( const checkedMatrix & m, const char * s )
{
   printf( "%s: %g\n", s, m(4,2) ) ;
}

void outofbounds( const uncheckedMatrix & m, const char * s ) noexcept
{
   printf( "%s: %g\n", s, m(4,2) ) ;
}

void outofbounds( const uncheckedMatrix2 & m, const char * s ) noexcept
{
   printf( "%s: %g\n", s, m(4,2) ) ;
}
