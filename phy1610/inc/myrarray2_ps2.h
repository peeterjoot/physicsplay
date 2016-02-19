/** \file myrarray2.h
 */
#if !defined phy1610_myrarray2_h_included
#define phy1610_myrarray2_h_included

#include <vector>
#include <algorithm>
#include <numeric>

#if defined MYRARRAY_USING_RARRAY
   #include "rarray"
#endif

//FIXME: should use dynamic allocation in myrarray for vector storage.
/**
   A class to manage the storage of and simple operations on a 2x2 dynamically allocated square array.

   If MYRARRAY_USING_RARRAY is defined, this will use rarray<float,2>(sz,sz) to hold the array.

   If MYRARRAY2_USE_STD_VECTOR is defined, this will use (a 1D) std::vector[sz*sz] to hold the array.

   Otherwise, this will use (1D) float [sz*sz] (heap allocated) storage to hold the array.
 */
class myrarray2
{
   using valueType = float ;

#if defined MYRARRAY_USING_RARRAY
   rarray<valueType, 2>    m_storage ;
#elif defined MYRARRAY2_USE_STD_VECTOR
   std::vector<valueType>  m_storage ;
#else
   valueType *             m_storage ;
#endif
   size_t                  m_sz ;

public:

   /** default constructor for empty array
    */
#if defined MYRARRAY2_USE_STD_VECTOR || defined MYRARRAY_USING_RARRAY
   inline myrarray2( ) : m_storage{}, m_sz{0}
#else
   inline myrarray2( ) : m_storage{nullptr}, m_sz{0}
#endif
   {
   }

   /** construct a 2x2 array without filling.
    */
#if defined MYRARRAY_USING_RARRAY
   inline myrarray2( const size_t sz ) : m_storage( sz, sz ), m_sz{sz}
#elif defined MYRARRAY2_USE_STD_VECTOR
   inline myrarray2( const size_t sz ) : m_storage( sz * sz ), m_sz{sz}
#else
   inline myrarray2( const size_t sz ) : m_storage{ new float[sz * sz] }, m_sz{sz}
#endif
   {
   }

   /** fill the 2x2 array with a value.
    */
   inline void fill( const valueType v )
   {
#if defined MYRARRAY_USING_RARRAY
      m_storage.fill( v ) ;
#elif defined MYRARRAY2_USE_STD_VECTOR
      std::fill( m_storage.begin(), m_storage.end(), v ) ;
#else
      std::fill( &m_storage[0], &m_storage[m_sz * m_sz], v ) ;
#endif
   }

   /** construct a 2x2 array and supply an initial value to the array.
    */
#if defined MYRARRAY_USING_RARRAY
   inline myrarray2( const size_t sz, const valueType v ) : m_storage( sz, sz ), m_sz{sz}
#elif defined MYRARRAY2_USE_STD_VECTOR
   inline myrarray2( const size_t sz, const valueType v ) : m_storage( sz * sz, v ), m_sz{sz}
#else
   inline myrarray2( const size_t sz, const valueType v ) : m_storage{ new float[sz * sz] }, m_sz{sz}
#endif
   {
#if !defined MYRARRAY2_USE_STD_VECTOR
      fill( v ) ;
#endif
   }

   /**
      Fetch the array(r,c) value from the underlying storage.
    */
   inline valueType operator()( const size_t r, const size_t c ) const
   {
#if defined MYRARRAY_USING_RARRAY
      return m_storage[ r ][ c ] ;
#else
      return m_storage[ r * m_sz + c ] ;
#endif
   }

   /**
      Assign a value v to the array(r,c) position in the array.
    */
   inline void assign( const size_t r, const size_t c, const valueType v )
   {
#if defined MYRARRAY_USING_RARRAY
      m_storage[ r ][ c ] = v ;
#else
      m_storage[ r * m_sz + c ] = v ;
#endif
   }

   /**
      Add a value v to the array(r,c) position in the array.
    */
   inline void add( const size_t r, const size_t c, const valueType v )
   {
#if defined MYRARRAY_USING_RARRAY
      m_storage[ r ][ c ] += v ;
#else
      m_storage[ r * m_sz + c ] += v ;
#endif
   }

   /**
      Swap the pointers for two sets of arrays.

      For an rarray<float,2> implementation this relies on reference counting and a temporary
      to swap things around.
    */
   inline void swap( myrarray2 & other )
   {
      std::swap( m_storage, other.m_storage ) ; // should also work for vector backed storage.
      std::swap( m_sz, other.m_sz ) ;
   }

   /**
      Compute the sum of all values in the array.
    */
   inline valueType sum( ) const
   {
      valueType total ;

      total = 0.0 ;

#if defined MYRARRAY_USING_RARRAY
      for ( size_t i = 0 ; i < m_sz ; i++ )
      {
         for ( size_t j = 0 ; j < m_sz ; j++ )
         {
#if defined MYRARRAY_USING_RARRAY
            total += m_storage[i][j] ;
#else
            total += m_storage[ i * m_sz + j ] ;
#endif
         }
      }

#elif defined MYRARRAY2_USE_STD_VECTOR
      total = std::accumulate( m_storage.begin(), m_storage.end(), 0.0f ) ;
#else
      total = std::accumulate( &m_storage[0], &m_storage[m_sz * m_sz], 0.0f ) ;
#endif

      return total ;
   }

   /** 
      overwrite this array with a different one.  Don't think I ended up using this?
    */
   inline myrarray2 & operator = ( const myrarray2 & b )
   {
#if defined MYRARRAY_USING_RARRAY
      m_storage = b.m_storage ;
      m_sz = b.m_sz ;
#else
      if ( m_sz == b.m_sz )
      {
#if defined MYRARRAY2_USE_STD_VECTOR
         std::copy( b.m_storage.begin(), b.m_storage.end(), m_storage.begin() ) ;
#else
         std::copy( &b.m_storage[0], &b.m_storage[m_sz * m_sz], &m_storage[0] ) ;
#endif
      }
      else
      {
#if defined MYRARRAY2_USE_STD_VECTOR
         m_storage = b.m_storage ;
#else
         if ( m_storage )
         {
            delete[] m_storage ;
         }

         m_storage = new float[ m_sz * m_sz] ;

         std::copy( &b.m_storage[0], &b.m_storage[m_sz * m_sz], &m_storage[0] ) ;
#endif
         m_sz = b.m_sz ;
      }
#endif

      return *this ;
   }
} ;

#endif
