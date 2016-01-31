/** \file myrarray2.h
 */
#if !defined phy1610_myrarray2_h_included
#define phy1610_myrarray2_h_included

#include <vector>
#include <algorithm>

/**
   A simple 2x2 dynamically allocated array construct.
 */
class myrarray2
{
   using valueType = float ;

#if defined MYRARRAY2_USE_STD_VECTOR
   std::vector<valueType>  m_storage ;
#else
   valueType *             m_storage ;
#endif
   size_t                  m_sz ;

public:
#if defined MYRARRAY2_USE_STD_VECTOR
   inline myrarray2( ) : m_storage{}, m_sz{0}
#else
   inline myrarray2( ) : m_storage{nullptr}, m_sz{0}
#endif
   {
   }

#if defined MYRARRAY2_USE_STD_VECTOR
   inline myrarray2( const size_t sz ) : m_storage( sz * sz ), m_sz{sz}
#else
   inline myrarray2( const size_t sz ) : m_storage{ new float[sz * sz] }, m_sz{sz}
#endif
   {
   }

   inline void fill( const valueType v )
   {
      std::fill( &m_storage[0], &m_storage[m_sz * m_sz], v ) ;
   }

#if defined MYRARRAY2_USE_STD_VECTOR
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
      return m_storage[ r * m_sz + c ] ;
   }

   inline void assign( const size_t r, const size_t c, const valueType v )
   {
      m_storage[ r * m_sz + c ] = v ;
   }

   inline void add( const size_t r, const size_t c, const valueType v )
   {
      m_storage[ r * m_sz + c ] += v ;
   }

   inline myrarray2 & operator = ( const myrarray2 & b )
   {
      if ( m_sz == b.m_sz )
      {
         std::copy( &b.m_storage[0], &b.m_storage[m_sz * m_sz], &m_storage[0] ) ;
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

      return *this ;
   }
} ;

#endif
