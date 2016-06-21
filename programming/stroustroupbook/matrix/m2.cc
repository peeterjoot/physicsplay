#include "matrix.h"

matrix f()
{
   matrix d( {1,2,3} ) ;   

   return d ;
}

void g( matrix & m )
{
   m = matrix( {1,2,3} ) ;   
}
