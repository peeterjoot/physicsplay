/** \file randomgenerators.h
 */
#if !defined phy1610_randomgenerators_h_included
#define phy1610_randomgenerators_h_included

#include <random>
#include "myassert.h"

//using my_random_engine = std::default_random_engine ;
using my_random_engine = std::mt19937 ;

/**
   A random number generator that produces integer uniformly
   distributed in the interval:

   [a, a + delta N]

   with separation delta between values returned.
 */
template <int a, int delta, int N>
class RandomIntegers
{
   std::random_device                        m_rd ;
   my_random_engine                          m_engine ;
   std::uniform_int_distribution<unsigned>   m_uniform ;

public:
   /** constuct a uniform random number generator for the specified range */
   RandomIntegers( )
      : m_rd()
      , m_engine( m_rd() )
      , m_uniform( 0, N )
   {
      static_assert( N > 0, "Integer N > 0 expected" ) ;
      static_assert( delta > 0, "Integer delta > 0 expected" ) ;
   }

   /**
      return a uniform random number sample from {a, a + delta, ..., a + delta N}
    */
   int sample()
   {
      auto p = m_uniform( m_engine ) ;

      return a + p * delta ;
   }
} ;

/**
   A random number generator that produces uniformly
   distributed values from the set

   {a, a + delta, ..., a + N delta}
 */
template <int N>
class RandomDiscreteReals
{
   std::random_device                        m_rd ;
   double                                    m_a ;       ///< lower interval bound
   double                                    m_delta ;   ///< separation between random number samples
   my_random_engine                          m_engine ;
   std::uniform_int_distribution<unsigned>   m_uniform ;

public:
   /** constuct a uniform random number generator for the specified range */
   RandomDiscreteReals( const double a, const double delta )
      : m_rd()
      , m_a( a )
      , m_delta( delta )
      , m_engine( m_rd() )
      , m_uniform( 0, N )
   {
      static_assert( N > 0, "Real N > 0 expected" ) ;
      myassert( delta > 0 ) ;
   }

   /**
      return a uniform random number sample from {a, a + delta, ..., a + delta N}
    */
   auto sample()
   {
      auto p = m_uniform( m_engine ) ;

      return m_a + p * m_delta ;
   }
} ;

/**
   A random number generator for float, double, or long double types, that produces uniformly
   distributed real values in the interval:

   [a, b]
 */
template <typename T = double>
class RandomReals
{
   std::random_device                  m_rd ;
   T                                   m_a ;        ///< lower interval bound
   T                                   m_b ;        ///< upper interval bound
   my_random_engine                    m_engine ;
   std::uniform_real_distribution<T>   m_uniform ;

public:
   /** constuct a uniform random number generator for the specified range */
   RandomReals( const T a, const T b )
      : m_rd()
      , m_a( a )
      , m_b( b )
      , m_engine( m_rd() )
      , m_uniform( a, b )
   {
      myassert( a < b ) ;
   }

   /**
      return a uniform random number sample from [a, b]
    */
   auto sample()
   {
      return m_uniform( m_engine ) ;
   }
} ;

#endif
