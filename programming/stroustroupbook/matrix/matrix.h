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

   matrix( const std::initializer_list<T> & diagonals ) 
      : sz{ diagonals.size() }
      , e( sz, sz )
   {
      std::cout << "create diagonal ( " << sz << " ): " << this << '\n' ;

      unsigned i = 0 ;
      
      for ( const auto & v : diagonals )
      {
         e[ i * sz + i ] = v ;
         i++ ;
      }
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
