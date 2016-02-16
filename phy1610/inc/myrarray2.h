/** \file myrarray2.h
 */
#if !defined phy1610_myrarray2_h_included
#define phy1610_myrarray2_h_included

#include <algorithm>
#include <numeric>
#include <vector>
#include <valarray>
#include "rarray"

//FIXME: should use dynamic allocation in myrarray for vector and/or valarray storage?

/**
   A class to manage the storage of and simple operations on a 2x2 dynamically allocated square array using 
   rarray<float,2>(sz,sz) to hold the array.
 */
class rarray2
{
   using valueType = float ;

   rarray<valueType, 2>    m_storage ;
   size_t                  m_sz ;

public:

   /** default constructor for empty array
    */
   inline rarray2( ) : m_storage{}, m_sz{0}
   {
   }

   /** construct a 2x2 array without filling.
    */
   inline rarray2( const size_t sz ) : m_storage( sz, sz ), m_sz{sz}
   {
   }

   /** fill the 2x2 array with a value.
    */
   inline void fill( const valueType v )
   {
      m_storage.fill( v ) ;
   }

   /** construct a 2x2 array and supply an initial value to the array.
    */
   inline rarray2( const size_t sz, const valueType v ) : m_storage( sz, sz ), m_sz{sz}
   {
      fill( v ) ;
   }

   /**
      Fetch the array(r,c) value from the underlying storage.
    */
   inline valueType operator()( const size_t r, const size_t c ) const
   {
      return m_storage[ r ][ c ] ;
   }

   /**
      Assign a value v to the array(r,c) position in the array.
    */
   inline void assign( const size_t r, const size_t c, const valueType v )
   {
      m_storage[ r ][ c ] = v ;
   }

   /**
      Add a value v to the array(r,c) position in the array.
    */
   inline void add( const size_t r, const size_t c, const valueType v )
   {
      m_storage[ r ][ c ] += v ;
   }

   /**
      Swap the pointers for two sets of arrays.

      For an rarray<float,2> implementation this relies on reference counting and a temporary
      to swap things around.
    */
   inline void swap( rarray2 & other )
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

      for ( size_t i = 0 ; i < m_sz ; i++ )
      {
         for ( size_t j = 0 ; j < m_sz ; j++ )
         {
            total += m_storage[i][j] ;
         }
      }

      return total ;
   }

#if 0
   /** 
      overwrite this array with a different one.  Don't think I ended up using this?
    */
   inline rarray2 & operator = ( const rarray2 & b )
   {
      m_storage = b.m_storage ;
      m_sz = b.m_sz ;

      return *this ;
   }
#endif
} ;

/**
   A class to manage the storage of and simple operations on a 2x2 dynamically allocated square array,
   this will use (a 1D) std::vector[sz*sz] to hold the array.
 */
class vecarray2
{
   using valueType = float ;

   std::vector<valueType>  m_storage ;
   size_t                  m_sz ;

public:

   /** default constructor for empty array
    */
   inline vecarray2( ) : m_storage{}, m_sz{0}
   {
   }

   /** construct a 2x2 array without filling.
    */
   inline vecarray2( const size_t sz ) : m_storage( sz * sz ), m_sz{sz}
   {
   }

   /** fill the 2x2 array with a value.
    */
   inline void fill( const valueType v )
   {
      std::fill( m_storage.begin(), m_storage.end(), v ) ;
   }

   /** construct a 2x2 array and supply an initial value to the array.
    */
   inline vecarray2( const size_t sz, const valueType v ) : m_storage( sz * sz, v ), m_sz{sz}
   {
   }

   /**
      Fetch the array(r,c) value from the underlying storage.
    */
   inline valueType operator()( const size_t r, const size_t c ) const
   {
      return m_storage[ r * m_sz + c ] ;
   }

   /**
      Assign a value v to the array(r,c) position in the array.
    */
   inline void assign( const size_t r, const size_t c, const valueType v )
   {
      m_storage[ r * m_sz + c ] = v ;
   }

   /**
      Add a value v to the array(r,c) position in the array.
    */
   inline void add( const size_t r, const size_t c, const valueType v )
   {
      m_storage[ r * m_sz + c ] += v ;
   }

   /**
      Swap the pointers for two sets of arrays.

      For an rarray<float,2> implementation this relies on reference counting and a temporary
      to swap things around.
    */
   inline void swap( vecarray2 & other )
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

      total = std::accumulate( m_storage.begin(), m_storage.end(), 0.0f ) ;

      return total ;
   }

#if 0
   /** 
      overwrite this array with a different one.  Don't think I ended up using this?
    */
   inline vecarray2 & operator = ( const vecarray2 & b )
   {
      if ( m_sz == b.m_sz )
      {
         std::copy( b.m_storage.begin(), b.m_storage.end(), m_storage.begin() ) ;
      }
      else
      {
         m_storage = b.m_storage ;
         m_sz = b.m_sz ;
      }

      return *this ;
   }
#endif
} ;

/**
   A class to manage the storage of and simple operations on a 2x2 dynamically allocated square array,
   this will use (a 1D) std::valarray[sz*sz] to hold the array.
 */
class valarray2
{
   using valueType = float ;

   std::valarray<valueType>  m_storage ;
   size_t                  m_sz ;

public:

   /** default constructor for empty array
    */
   inline valarray2( ) : m_storage{}, m_sz{0}
   {
   }

   /** construct a 2x2 array without filling.
    */
   inline valarray2( const size_t sz ) : m_storage( sz * sz ), m_sz{sz}
   {
   }

   /** fill the 2x2 array with a value.
    */
   inline void fill( const valueType v )
   {
      m_storage = v ;
   }

   /** construct a 2x2 array and supply an initial value to the array.
    */
   inline valarray2( const size_t sz, const valueType v ) : m_storage( sz * sz, v ), m_sz{sz}
   {
   }

   /**
      Fetch the array(r,c) value from the underlying storage.
    */
   inline valueType operator()( const size_t r, const size_t c ) const
   {
      return m_storage[ r * m_sz + c ] ;
   }

   /**
      Assign a value v to the array(r,c) position in the array.
    */
   inline void assign( const size_t r, const size_t c, const valueType v )
   {
      m_storage[ r * m_sz + c ] = v ;
   }

   /**
      Add a value v to the array(r,c) position in the array.
    */
   inline void add( const size_t r, const size_t c, const valueType v )
   {
      m_storage[ r * m_sz + c ] += v ;
   }

   /**
      Swap the pointers for two sets of arrays.

      For an rarray<float,2> implementation this relies on reference counting and a temporary
      to swap things around.
    */
   inline void swap( valarray2 & other )
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

      total = m_storage.sum() ;

      return total ;
   }

#if 0
   /** 
      overwrite this array with a different one.  Don't think I ended up using this?
    */
   inline valarray2 & operator = ( const valarray2 & b )
   {
      if ( m_sz == b.m_sz )
      {
         m_storage = b.m_storage ;
      }
      else
      {
         m_storage = b.m_storage ;
         m_sz = b.m_sz ;
      }

      return *this ;
   }
#endif
} ;

/**
   A class to manage the storage of and simple operations on a 2x2 dynamically allocated square array,
   this will use (a 1D) float[sz*sz] storage to hold the array.
 */
class farray2
{
   using valueType = float ;

   valueType *             m_storage ;
   size_t                  m_sz ;

public:

   /** default constructor for empty array
    */
   inline farray2( ) : m_storage{nullptr}, m_sz{0}
   {
   }

   /** construct a 2x2 array without filling.
    */
   inline farray2( const size_t sz ) : m_storage{ new float[sz * sz] }, m_sz{sz}
   {
   }

   /** fill the 2x2 array with a value.
    */
   inline void fill( const valueType v )
   {
      std::fill( &m_storage[0], &m_storage[m_sz * m_sz], v ) ;
   }

   /** construct a 2x2 array and supply an initial value to the array.
    */
   inline farray2( const size_t sz, const valueType v ) : m_storage{ new float[sz * sz] }, m_sz{sz}
   {
      fill( v ) ;
   }

   /**
      Fetch the array(r,c) value from the underlying storage.
    */
   inline valueType operator()( const size_t r, const size_t c ) const
   {
      return m_storage[ r * m_sz + c ] ;
   }

   /**
      Assign a value v to the array(r,c) position in the array.
    */
   inline void assign( const size_t r, const size_t c, const valueType v )
   {
      m_storage[ r * m_sz + c ] = v ;
   }

   /**
      Add a value v to the array(r,c) position in the array.
    */
   inline void add( const size_t r, const size_t c, const valueType v )
   {
      m_storage[ r * m_sz + c ] += v ;
   }

   /**
      Swap the pointers for two sets of arrays.

      For an rarray<float,2> implementation this relies on reference counting and a temporary
      to swap things around.
    */
   inline void swap( farray2 & other )
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

      total = std::accumulate( &m_storage[0], &m_storage[m_sz * m_sz], 0.0f ) ;

      return total ;
   }

#if 0
   /** 
      overwrite this array with a different one.  Don't think I ended up using this?
    */
   inline farray2 & operator = ( const farray2 & b )
   {
      if ( m_sz == b.m_sz )
      {
         std::copy( &b.m_storage[0], &b.m_storage[m_sz * m_sz], &m_storage[0] ) ;
      }
      else
      {
         if ( m_storage )
         {
            delete[] m_storage ;
         }

         m_storage = new float[ m_sz * m_sz] ;

         std::copy( &b.m_storage[0], &b.m_storage[m_sz * m_sz], &m_storage[0] ) ;
         m_sz = b.m_sz ;
      }

      return *this ;
   }
#endif
} ;

#if !defined MYRARRAY_USING_RARRAY && \
    !defined MYRARRAY2_USE_STD_VECTOR && \
    !defined MYRARRAY_USING_VALARRAY && \
    !defined MYRARRAY_USING_FLOATARR

#define myrarray2 farray2
   #define MYRARRAY_USING_VALARRAY
   //#define MYRARRAY_USING_FLOATARR
   //#define MYRARRAY_USING_RARRAY
   //#define MYRARRAY2_USE_STD_VECTOR
#endif

#endif
