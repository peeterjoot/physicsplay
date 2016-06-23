#if !defined __matrix_header_included
#define __matrix_header_included

#include <vector>
#include <iostream>

// A simple square matrix implementation
class matrix
{
   using T = int ;

   size_t            sz ;
   std::vector<T>    e ;

public:

   enum class initMethod { DIAGONALS } ;

   matrix( unsigned n ) 
      : sz{ n }
      , e( n * n )
   {
      std::cout << "create << " << sz << " x " << sz << ": " << this << '\n' ;
   }

   unsigned size() const
   {
      return sz ;
   }

   matrix( const size_t n, const size_t m, const std::initializer_list<T> & diagonals ) ;

   matrix( const std::initializer_list<T> & diagonals )
      : matrix( diagonals.size(), diagonals.size(), diagonals )
   {
   }

   matrix( matrix && m )
      : sz{ m.sz }
      , e{ std::move(m.e) }
   {
      m.sz = 0 ;
      std::cout << "move construction: " << &m << " to " << this << " ; m.e.size(): " << m.e.size() << '\n' ;
   }

   matrix & operator = ( matrix && m )
   {
      std::cout << "move operator=(): " << this << '\n' ;

      std::swap( sz, m.sz ) ;
      std::swap( e, m.e ) ;

      return *this ;
   }

   matrix( const matrix & m )
      : sz{ m.sz }
      , e{ m.e }
   {
      std::cout << "copied: " << &m << " to " << this << '\n' ;
   }

   matrix & operator = ( const matrix & m )
   {
      std::cout << "copy operator = : " << this << '\n' ;

      matrix t{ m } ;
      std::swap( sz, t.sz ) ;
      std::swap( e, t.e ) ;

      return *this ;
   }

   ~matrix()
   {
      std::cout << "destroy: " << this << '\n' ;
   }

   friend std::ostream & operator <<( std::ostream & o, const matrix & m ) ;
} ;

#endif
