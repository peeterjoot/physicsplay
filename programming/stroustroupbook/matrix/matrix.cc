#include "matrix.h"
#include <stdexcept>
#include <string>
#include <algorithm>

std::ostream & operator<< ( std::ostream & o, const matrix & m )
{
//   o << "sz: " << m.sz
//     << ", m_elem.sz: " << m.m_elem.size() 
//     << '\n' ;

   unsigned i = 1 ;
   auto rows = m.m_rows ;
   auto columns = m.m_columns ;

   for ( const auto & e : m.m_elem )
   {
      char sep ;

      if ( (i % columns) == 0 )
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

matrix::matrix( const size_t rows_, const size_t columns_, const std::initializer_list<T> & diagonals ) 
   : m_rows{ rows_ }
   , m_columns{ columns_ }
   , m_elem( m_rows * m_columns )
{
   std::cout << "create diagonal ( " << diagonals.size() << " ): " << this << '\n' ;

   if ( std::max(m_rows, m_columns) > diagonals.size() )
   {
      std::string what { "incompatible initializer vector of size " + std::to_string( diagonals.size() ) + " with matrix dimensions (rows, columns) = " + std::to_string(m_rows) + ", " + std::to_string(m_columns) } ;

      throw std::range_error( what ) ;
   }

   unsigned d = 0 ;
   
   for ( const auto & v : diagonals )
   {
      m_elem[ d * m_columns + d ] = v ;
      d++ ;
   }
}
