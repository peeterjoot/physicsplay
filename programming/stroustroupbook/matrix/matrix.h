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
      std::cout << "create n x n: " << this << '\n' ;
   }

   unsigned size() const
   {
      return sz ;
   }

   matrix( const std::initializer_list<T> & diagonals ) 
      : sz{ diagonals.size() }
      , e( sz, sz )
   {
      std::cout << "create diagonal: " << this << '\n' ;

      unsigned i = 0 ;
      
      for ( const auto & v : diagonals )
      {
         e[ i * sz + i ] = v ;
         i++ ;
      }
   }

   //friend std::ostream & operator <<( std::ostream & o, const matrix & m ) ;

   //matrix( matrix && m ) = default ;
   matrix( matrix && m )
      : sz{ m.sz }
      , e{ std::move(m.e) }
   {
      m.sz = 0 ;
      std::cout << "moved: " << &m << " to " << this << " ; m.e.size(): " << m.e.size() << '\n' ;
   }

#if 0
   matrix & operator = ( matrix && m ) = default ;
#else
   matrix & operator = ( matrix && m )
   {
      std::cout << "move operator = : " << this << '\n' ;

      std::swap( sz, m.sz ) ;
      std::swap( e, m.e ) ;

      return *this ;
   }
#endif

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
} ;

#endif
