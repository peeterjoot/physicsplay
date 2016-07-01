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
      matrix::indexType sz ;
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

   void throwRangeError( const indexType i, const indexType j ) const
   {
      throw rangeError{ i, j, size } ;
   }

   /**
      Introduce a virtual function that allows user selection of optional range error checking.
    */
   virtual
   void handleRangeError( const indexType i, const indexType j ) const
   {
      throwRangeError( i, j ) ;
   }

   bool areIndexesOutOfRange( const indexType i, const indexType j ) const
   {
      if ( (0 == i) or (0 == j) or (i > size) or (j > size) )
      {
         return true ;
      }

      return false ;
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

   T operator()( const indexType i, const indexType j ) const
   {
      if ( areIndexesOutOfRange( i, j ) )
      {
         handleRangeError( i, j ) ;
      }

      return access( i, j ) ;
   }
} ;

/**
   Explicitly unchecked matrix element access
 */
class uncheckedMatrix : public matrix
{
public:
   // inherit constructors:
   using matrix::matrix ;

   void handleRangeError( const indexType i, const indexType j ) const final
   {
   }
} ;

/**
   Explicitly unchecked matrix element access
 */
class uncheckedMatrix2 : public matrix
{
public:
   // inherit constructors:
   using matrix::matrix ;

   void handleRangeError( const indexType i, const indexType j ) const final
   {
   }

   T operator()( const indexType i, const indexType j ) const
   {
      return access( i, j ) ;
   }
} ;

/**
   Explicitly checked matrix element access
 */
class checkedMatrix : public matrix
{
public:
   // inherit constructors:
   using matrix::matrix ;

   void handleRangeError( const indexType i, const indexType j ) const final
   {
      throwRangeError( i, j ) ;
   }
} ;

#endif
