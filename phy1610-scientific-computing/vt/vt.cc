#include "integers.h"
#include <valarray>
#include <cstdlib>
#include <cmath>
//#include <chrono>
#include <iostream>
#include "ticks.h"

//using namespace std ;

inline float randomTx( const float & unused )
{
   (void)unused ;

   return (float)rand()/RAND_MAX ;
}

void initialize( std::valarray<float> & v, Uint n ) ;

void SineCosineManOps( std::valarray<float> & s, std::valarray<float> & c, const std::valarray<float> & v ) ;
void SineCosineVecOps( std::valarray<float> & s, std::valarray<float> & c, const std::valarray<float> & v ) ;

static constexpr auto ASIZE{ 300 } ;

int main()
{
   std::valarray<float> v( ASIZE ) ;
   std::valarray<float> s( ASIZE ) ;
   std::valarray<float> c( ASIZE ) ;
   std::valarray<float> sm( ASIZE ) ;
   std::valarray<float> cm( ASIZE ) ;
   ticks::duration vectorTime{} ;
   ticks::duration manualTime{} ;

   for ( Uint j{0} ; j < 500 ; j++ )
   {
      initialize( v, j ) ;

      auto t0 = ticks::sample() ;
      SineCosineVecOps( s, c, v ) ;
      auto t1 = ticks::sample() ;

      vectorTime += (t1 - t0) ;

      auto t2 = ticks::sample() ;
      SineCosineManOps( sm, cm, v ) ;
      auto t3 = ticks::sample() ;

      manualTime += (t3 - t2) ;
   }

   auto vMicro { durationToMicroseconds( vectorTime ) } ;
   auto mMicro { durationToMicroseconds( manualTime ) } ;

   std::cout << "vectorTime: " << vMicro << '\n' ;
   std::cout << "manualTime: " << mMicro << '\n' ;
   std::cout << "vectorTime/manualTime: " << (double)vMicro/mMicro << std::endl ;

   float si = s.sum() ;
   float co = c.sum() ;
   printf( "%f %f\n", si, co ) ;

   return 0 ;
}

void initialize( std::valarray<float> & v, Uint n )
{
   if ( 0 == n )
   {
      v = v.apply( randomTx ) * M_PI ;
   }
}

void SineCosineVecOps( std::valarray<float> & s, std::valarray<float> & c, const std::valarray<float> & v )
{
   s = std::sin( v ) ;
   c = std::cos( v ) ;
}

void SineCosineManOps( std::valarray<float> & s, std::valarray<float> & c, const std::valarray<float> & v )
{
   for ( Uint i{0} ; i < ASIZE ; i++ )
   {
      float theta = v[i] ;

      s[i] = std::sin( theta ) ;
      c[i] = std::cos( theta ) ;
   }
}
