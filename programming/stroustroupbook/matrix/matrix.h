#if !defined __matrix_header_included
#define __matrix_header_included

#include <vector>
#include <iostream>

// A simple square matrix implementation
class matrix
{
   using T = int ;

   size_t            m_rows ;
   size_t            m_columns ;
   std::vector<T>    m_elem ;

public:

   /// create square matrix with n rows
   matrix( unsigned n ) 
      : m_rows{ n }
      , m_columns{ n }
      , m_elem( n * n )
   {
      std::cout << "create << " << m_rows << " x " << m_columns << ": " << this << '\n' ;
   }

   unsigned rows() const
   {
      return m_rows ;
   }

   unsigned columns() const
   {
      return m_columns ;
   }

   /// Create diagonal matrix with specified number of rows and columns
   matrix( const size_t rows, const size_t columns, const std::initializer_list<T> & diagonals ) ;

   /// Create (dense) square matrix with the specified diagonal elements.
   matrix( const std::initializer_list<T> & diagonals )
      : matrix( diagonals.size(), diagonals.size(), diagonals )
   {
   }

   matrix( matrix && m )
      : m_rows{ m.m_rows }
      , m_columns{ m.m_columns }
      , m_elem{ std::move(m.m_elem) }
   {
      m.m_rows = 0 ;
      m.m_columns = 0 ;
      std::cout << "move construction: " << &m << " to " << this << " ; dimensions: (rows, columns) = ( " << rows() << ", " << columns() << " )\n" ;
   }

   matrix & operator = ( matrix && m )
   {
      std::cout << "move operator=(): " << this << '\n' ;

      std::swap( m_columns, m.m_columns ) ;
      std::swap( m_rows, m.m_rows ) ;
      std::swap( m_elem, m.m_elem ) ;

      return *this ;
   }

   matrix( const matrix & m )
      : m_columns{ m.m_columns }
      , m_rows{ m.m_rows }
      , m_elem{ m.m_elem }
   {
      std::cout << "copied: " << &m << " to " << this << '\n' ;
   }

   matrix & operator = ( const matrix & m )
   {
      std::cout << "copy operator = : " << this << '\n' ;

      matrix t{ m } ;
      std::swap( m_rows, t.m_rows ) ;
      std::swap( m_columns, t.m_columns ) ;
      std::swap( m_elem, t.m_elem ) ;

      return *this ;
   }

   ~matrix()
   {
      std::cout << "destroy: " << this << '\n' ;
   }

   friend std::ostream & operator <<( std::ostream & o, const matrix & m ) ;
} ;

#endif
