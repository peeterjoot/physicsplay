/** \file randomgenerators.h
 */
#if !defined phy1610_randomgenerators_h_included
#define phy1610_randomgenerators_h_included

#include <random>
#include <cassert>

/**
   A random number generator that produces integer uniformly
   distributed in the interval:

   [a, a + delta N]

   with separation delta between values returned.
 */
template <int a, int delta, int N>
class RandomIntegers
{
   std::default_random_engine                m_engine ;
   std::uniform_int_distribution<unsigned>   m_uniform ;

public:
   /** constuct a uniform random number generator for the specified range */
   RandomIntegers()
      : m_uniform( 0, N )
   {
      static_assert( N > 0, "Integer N > 0 expected" ) ;
      static_assert( delta > 0, "Integer delta > 0 expected" ) ;
   }

   /**
      Reset the seed for the random number generator.

      \param seed [in]
         A value a + n delta, where n is an integer in [0, N]
    */
   void start( const int seed )
   {
      assert( seed >= a ) ;
      assert( seed <= (a + N * delta) ) ;
      assert( 0 == (( seed - a) % delta) ) ;

      int p = (seed - a)/delta ;

      m_engine.seed( p ) ;
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
   double                                    m_a ;       ///< lower interval bound
   double                                    m_delta ;   ///< separation between random number samples
   std::default_random_engine                m_engine ;
   std::uniform_int_distribution<unsigned>   m_uniform ;

public:
   /** constuct a uniform random number generator for the specified range */
   RandomDiscreteReals( const double a, const double delta )
      : m_a( a )
      , m_delta( delta )
      , m_engine()
      , m_uniform( 0, N )
   {
      static_assert( N > 0, "Real N > 0 expected" ) ;
      assert( delta > 0 ) ;
   }

   /**
      Reset the seed for the random number generator.

      \param seed [in]
         A value a + n delta, where n is an integer in [0, N]
    */
   void start( const double seed )
   {
      assert( seed >= m_a ) ;
      assert( seed <= (m_a + N * m_delta) ) ;
      //assert( 0 == (( seed - a) % delta) ) ;

      int p = (seed - m_a)/m_delta ;

      m_engine.seed( p ) ;
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
   T                                   m_a ;        ///< lower interval bound
   T                                   m_b ;        ///< upper interval bound
   std::default_random_engine          m_engine ;
   std::uniform_real_distribution<T>   m_uniform ;

public:
   /** constuct a uniform random number generator for the specified range */
   RandomReals( const T a, const T b )
      : m_a( a )
      , m_b( b )
      , m_engine()
      , m_uniform( a, b )
   {
      assert( a < b ) ;
   }

   /**
      Reset the seed for the random number generator.

      \param seed [in]
         A value within the interval [a,b] supplied to the constructor of this random number generator.
    */
   void start( const T seed )
   {
      assert( seed >= m_a ) ;
      assert( seed <= m_b ) ;

      m_engine.seed( seed ) ;
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
