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

   matrix( matrix && m ) = default ;
#if 0
   matrix( matrix && m )
      : sz{ m.sz }
      , e{ std::move(m.e) }
   {
      m.sz = 0 ;
      std::cout << "moved: " << &m << " to " << this << " ; m.e.size(): " << m.e.size() << '\n' ;
   }
#endif

   matrix( const matrix & m )
      : sz{ m.sz }
      , e{ m.e }
   {
      std::cout << "copied: " << &m << " to " << this << '\n' ;
   }

   ~matrix()
   {
      std::cout << "destroy: " << this << '\n' ;
   }
} ;

#endif
