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

/**
   A simple 2x2 dynamically allocated array construct.
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
#if defined MYRARRAY2_USE_STD_VECTOR || defined MYRARRAY_USING_RARRAY
   inline myrarray2( ) : m_storage{}, m_sz{0}
#else
   inline myrarray2( ) : m_storage{nullptr}, m_sz{0}
#endif
   {
   }

#if defined MYRARRAY_USING_RARRAY
   inline myrarray2( const size_t sz ) : m_storage( sz, sz ), m_sz{sz}
#elif defined MYRARRAY2_USE_STD_VECTOR
   inline myrarray2( const size_t sz ) : m_storage( sz * sz ), m_sz{sz}
#else
   inline myrarray2( const size_t sz ) : m_storage{ new float[sz * sz] }, m_sz{sz}
#endif
   {
   }

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

   inline void swap( myrarray2 & other )
   {
      std::swap( m_storage, other.m_storage ) ; // should also work for vector backed storage.
      std::swap( m_sz, other.m_sz ) ;
   }

   inline valueType sum( ) const
   {
      valueType total ;

#if defined MYRARRAY_USING_RARRAY
      total = 0.0 ;

      for ( size_t i = 0 ; i < m_sz ; i++ )
      {
         for ( size_t j = 0 ; j < m_sz ; j++ )
         {
            total += m_storage[i][j] ;
         }
      }
#elif defined MYRARRAY2_USE_STD_VECTOR
      total = std::accumulate( m_storage.begin(), m_storage.end(), 0.0 ) ;
#else
      total = std::accumulate( &m_storage[0], &m_storage[m_sz * m_sz], 0.0 ) ;
#endif

      return total ;
   }

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

   inline valueType operator()( const size_t r, const size_t c ) const
   {
#if defined MYRARRAY_USING_RARRAY
      return m_storage[ r ][ c ] ;
#else
      return m_storage[ r * m_sz + c ] ;
#endif
   }

   inline void assign( const size_t r, const size_t c, const valueType v )
   {
#if defined MYRARRAY_USING_RARRAY
      m_storage[ r ][ c ] = v ;
#else
      m_storage[ r * m_sz + c ] = v ;
#endif
   }

   inline void add( const size_t r, const size_t c, const valueType v )
   {
#if defined MYRARRAY_USING_RARRAY
      m_storage[ r ][ c ] += v ;
#else
      m_storage[ r * m_sz + c ] += v ;
#endif
   }

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
