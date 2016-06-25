#include "matrix.h"

matrix f()
{
   std::cout << "f(): construct and return:\n" ;
   matrix d( {1,2,3} ) ;   

   return d ;
}

void g( matrix & m )
{
   std::cout << "g(): assignment\n" ;
   m = matrix( {1,2,3} ) ;   
}
