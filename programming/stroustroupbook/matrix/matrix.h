#if !defined __matrix_header_included
#define __matrix_header_included

#include <vector>
#include <iostream>

/// A simple square matrix skeleton, with instrumented copy, move, construction and destruction operators
class matrix
{
   using T = int ;                  ///< allow for easy future templatization.

   size_t            m_rows ;       ///< number of rows for the matrix.  May be zero.
   size_t            m_columns ;    ///< number of columns for the matrix.  May be zero.
   std::vector<T>    m_elem ;       ///< backing store for the matrix elements, stored in row major format.

public:

   /// create square matrix with n rows
   matrix( unsigned n ) 
      : m_rows{ n }
      , m_columns{ n }
      , m_elem( n * n )
   {
      std::cout << "create << " << m_rows << " x " << m_columns << ": " << this << '\n' ;
   }

   /// number of rows in the matrix
   unsigned rows() const
   {
      return m_rows ;
   }

   /// number of columns in the matrix
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

   /// move constructor to create 
   matrix( matrix && m )
      : m_rows{ m.m_rows }
      , m_columns{ m.m_columns }
      , m_elem{ std::move(m.m_elem) }
   {
      //std::cout << "move construction: (m.m_rows, m.m_columns) [after move] : " << m.m_rows << ", " << m.m_columns << "\n" ;
      //std::cout << "move construction: (m.m_elem.size()) [after move] : " << m.m_elem.size() << "\n" ;
      m.m_rows = 0 ;
      m.m_columns = 0 ;
      std::cout << "move construction: " << &m << " to " << this << " ; dimensions: (rows, columns, size) = ( " << rows() << ", " << columns() << ", " << m_elem.size() << " )\n" ;
   }

   /// move assignment operator.
   matrix & operator = ( matrix && m )
   {
      std::cout << "move operator=(): " << this << '\n' ;

      std::swap( m_columns, m.m_columns ) ;
      std::swap( m_rows, m.m_rows ) ;
      std::swap( m_elem, m.m_elem ) ;

      return *this ;
   }

   /// copy construction operator.
   matrix( const matrix & m )
      : m_columns{ m.m_columns }
      , m_rows{ m.m_rows }
      , m_elem{ m.m_elem }
   {
      std::cout << "copied: " << &m << " to " << this << '\n' ;
   }

   /// copy assignment operator.
   matrix & operator = ( const matrix & m )
   {
      std::cout << "copy operator = : " << this << '\n' ;

      matrix t{ m } ;
      std::swap( m_rows, t.m_rows ) ;
      std::swap( m_columns, t.m_columns ) ;
      std::swap( m_elem, t.m_elem ) ;

      return *this ;
   }

   /// destructor
   ~matrix()
   {
      std::cout << "destroy: " << this << '\n' ;
   }

   /// formatted text io for the matrix (space separated elements, with newlines between rows).
   friend std::ostream & operator <<( std::ostream & o, const matrix & m ) ;
} ;

#endif
