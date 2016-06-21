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
   }

   unsigned size() const
   {
      return sz ;
   }

   matrix( const std::initializer_list<T> & diagonals ) 
      : sz{ diagonals.size() }
      , e( sz, sz )
   {
      unsigned i = 0 ;
      
      for ( const auto & v : diagonals )
      {
         e[ i * sz + i ] = v ;
         i++ ;
      }
   }

   friend std::ostream & operator <<( std::ostream & o, const matrix & m ) ;

   matrix( matrix && m )
      : sz{ m.sz }
      , e{ }
   {
      m.sz = 0 ;
      std::swap( e, m.e ) ;
   }
} ;
