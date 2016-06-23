#include "matrix.h"

std::ostream & operator <<( std::ostream & o, const matrix & m )
{
//   o << "sz: " << m.sz
//     << ", e.sz: " << m.e.size() 
//     << '\n' ;

   unsigned i = 1 ;
   auto sz = m.sz ;

   for ( const auto & e : m.e )
   {
      char sep ;

      if ( (i % sz) == 0 )
      {
         sep = '\n' ;
      }
      else
      {
         sep = ' ' ;
      }

      o << e << sep ; 
      i++ ;
   }

   return o ;
}

// FIXME:
matrix::matrix( const size_t n, const size_t m, const std::initializer_list<T> & diagonals ) 
   : sz{ diagonals.size() }
   , e( sz * sz )
{
   std::cout << "create diagonal ( " << sz << " ): " << this << '\n' ;

   unsigned d = 0 ;
   
   for ( const auto & v : diagonals )
   {
      e[ d * sz + d ] = v ;
      d++ ;
   }
}
