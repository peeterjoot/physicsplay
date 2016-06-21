#include "matrix.h"

matrix f()
{
   matrix d( {1,2,3} ) ;   

   //return d ;
   return std::move( d ) ;
}
