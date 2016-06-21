#include "matrix.h"

std::ostream & operator <<( std::ostream & o, const matrix & m )
{
   o << "sz: " << m.sz
     << ", e.sz: " << m.e.size() 
     << '\n' ;

/*
   unsigned i = 0 ;
   const char * sep = ' ' ;
   for ( const auto & e : m.e )
   {
      o << e << sep ; 

      if ( i && ((i+1) % m.e.size() == 0)
      {
         sep = '\n' ;
      }
      else
      {
         sep = ' ' ;
      }
   }
*/

   return o ;
}

matrix f() ;

int main()
{
   matrix m{ f() } ;
//   std::cout << m ;

   return m.size() ;
}
