#ifndef my_matrix_header_included
#define my_matrix_header_included

#include <vector>
/// an NxN square matrix, indexed over [1..N]x[1..N]
class matrix
{
public:
   using T = double ;
   using indexType = size_t ;

   struct rangeError
   {
      matrix::indexType i ;
      matrix::indexType j ;
   } ;

private:
   std::vector<T> v ;
   size_t size{} ;

protected:
   // unchecked element access function:
   T access( const indexType i, const indexType j ) const
   {
      return v[ (i - 1)*size + j - 1 ] ;
   }

   void store( const T & x, const indexType i, const indexType j )
   {
      v[ (i - 1)*size + j - 1 ] = x ;
   }

   //virtual void checkIndexes( const indexType i, const indexType j ) const
   void checkIndexes( const indexType i, const indexType j ) const
   {
      if ( (0 == i) or (0 == j) or (i > size) or (j > size) )
      {
         throw rangeError{i, j} ;
      }
   }
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
         store( x, j, j ) ;

         j++ ;
      }
   }

   virtual T operator()( const indexType i, const indexType j ) const
   {
      checkIndexes( i, j ) ;

      return access( i, j ) ;
   }
} ;

class uncheckedMatrix : public matrix
{
public:
   // inherit constructors:
   using matrix::matrix ;

#if 0
   // not enough to just provide a final version of this function (if made virtual in the base class):
   //    call to operator()() still takes a vtbl hit.
   //
   void checkIndexes( const indexType i, const indexType j ) const final
   {
   }
#endif

   T operator()( const indexType i, const indexType j ) const final
   {
      return access( i, j ) ;
   }
} ;

#endif
