#include <vector>
//#include <iostream>
#include <stdio.h>

/// an NxN square matrix, indexed over [1..N]x[1..N]
class matrix
{
protected:
   using T = double ;
   using indexType = size_t ;

   std::vector<T> v ;
   size_t size{} ;

public:
   matrix( const indexType sz ) 
      : v( sz*sz )
      , size{sz}
   {
   }

   matrix( const std::initializer_list<T> & i )
      : v( i.size() * i.size() )
      , size{ i.size() }
   {
      indexType j{} ;

      for ( const auto & x : i )
      {
         v[ (j - 1)*size + j - 1 ] ;

         j++ ;
      }
   }

   virtual T operator()( const indexType i, const indexType j )
   {
      return v[ (i - 1)*size + j - 1 ] ;
   }
} ;

class checkedMatrix : public matrix
{
public:
   struct rangeError
   {
      matrix::indexType i ;
      matrix::indexType j ;
   } ;

   // inherit constructors:
   using matrix::matrix ;

   T operator()( const indexType i, const indexType j ) final
   {
      if ( (0 == i) or (0 == j) or (i > size) or (j > size) )
      {
         throw rangeError{i, j} ;
      }

      return v[ (i - 1)*size + j - 1 ] ;
   }
} ;

int main()
try {
   matrix m1{ 1., 2., 3. } ;

   printf( "%g\n", m1(4,4) ) ;
//   std::cout << m1(4,4) << '\n' ;

   checkedMatrix m2{ 1., 2., 3. } ;

   printf( "%g\n", m2(4,2) ) ;
//   std::cout << m2(4,4) << '\n' ;

   return 0 ;
}
catch ( checkedMatrix::rangeError & e )
{
   printf( "range error: i,j = %lu, %lu\n", e.i, e.j ) ;
//   std::cout << "range error: " << e.i << ", " << e.j << '\n' ;

   return 1 ;
}
