#include "matrix.h"

matrix f()
{
   matrix d( {1,2,3} ) ;   

   return std::move( d ) ;
}
