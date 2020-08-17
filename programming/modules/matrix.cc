#include <cstring>
#include "matrix.h"

void matrix::set( what w ) {
   std::memset( x, 0, sizeof(x) );

   if ( w == identity ) {
      for ( size_type i = 1 ; i <= size ; i++ ) {
         elem(i, i) = 1.0;
      }
   }
}
