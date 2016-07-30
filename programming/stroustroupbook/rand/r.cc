#include <random>
#include <functional>
#include <iostream>
#include <unordered_map>

/** bind uniform_int_distribution */
template < int a, int b >
class RandomIntegers
{  
   decltype( std::default_random_engine() )  m_device{ std::default_random_engine() } ;
   std::mt19937                              m_engine ;
   std::uniform_int_distribution<int>        m_uniform{ a, b } ;

public:
   /** constuct a uniform random number generator for the specified range */
   RandomIntegers( )
      : m_engine( m_device() )
   {  
   }

   int operator()()
   {
      return m_uniform( m_engine ) ;
   }
} ;

/** bind uniform_int_distribution */
class RandomIntegers2
{  
   //std::function<double()> m_r ;
   std::random_device                  m_dev{} ;
   std::uniform_int_distribution<>     m_dist ;

public:
   /** constuct a uniform random number generator for the specified range */
   RandomIntegers2( int a, int b )
      : m_dist( a, b )
   {  
   }

   int operator()()
   {
      return m_dist( m_dev ) ;
   }
} ;

/** bind uniform_int_distribution, copied from Stroustrup's "C++ Programming Language, 4th" */
class RandomIntegers3
{  
   std::uniform_int_distribution<>::param_type  m_params ;
   auto r = std::bind( uniform_int_distribution<>{ m_params }, std::default_random_engine{} ) ;

public:
   /** constuct a uniform random number generator for the specified range */
   RandomIntegers3( int a, int b )
      : m_params{ a, b }
   {  
   }

   int operator()()
   {
      return r() ;
   }
} ;

int main()
{
   std::unordered_map<int, int> buckets ;
//   RandomIntegers<-3, 6> r ;
//   RandomIntegers2 r( -3, 6 ) ;
   RandomIntegers3 r( -3, 6 ) ;

   std::cout << "Value\n" ;
   for ( int i{} ; i < 10000 ; i++ )
   {
      buckets[ r() ]++ ;
   }

   for ( auto v : buckets )
   {
      std::cout << v.first << ", " << v.second << '\n' ;
   }

   return 0 ;
}
