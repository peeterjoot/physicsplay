/**
   \file test.cc

   standalone simple test cases.
 */
#include "randomgenerators.h"
#include <iostream>
#include <string>

#define BOOST_TEST_MAIN
#define BOOST_TEST_MODULE test

#include "boosttest.h"

constexpr auto Nchecks{ 20 } ;

using FairCoin = RandomIntegers<-1, 2, 1> ;

void testFairCoin( FairCoin & c )
{
   for ( auto i = 0 ; i < Nchecks ; i++ )
   {
      auto v = c.sample() ;

      BOOST_REQUIRE( (v == -1) or (v == +1) ) ;
   }
}

BOOST_AUTO_TEST_CASE( testFC )
{
   FairCoin c ;

   testFairCoin( c ) ;

   for ( auto seed : {-1,1} )
   {
      c.start( seed ) ;

      testFairCoin( c ) ;
   }
}

inline bool equals( const double v1, const double v2 )
{
   constexpr auto tolerance{ 1e-8 } ;

   return std::abs( v1 - v2 ) < tolerance ;
}

using R2 = RandomDiscreteReals<2> ;

void testR2( R2 & r )
{
   for ( auto i = 0 ; i < Nchecks ; i++ )
   {
      auto v = r.sample() ;

      BOOST_REQUIRE_MESSAGE(
         equals( v, -0.5 ) or 
         equals( v, +0.5 ) or 
         equals( v, 0 ), "v = " + std::to_string(v) ) ;
   }
}

BOOST_AUTO_TEST_CASE( testRandomDiscreteReals )
{
   R2 r(-0.5, 0.5) ;

   testR2( r ) ;

   for ( auto seed : {-0.5, 0.0, 0.5} )
   {
      r.start( seed ) ;

      testR2( r ) ;
   }
}

using R3 = RandomReals<> ;

void testR3( R3 & s )
{
   for ( auto i = 0 ; i < Nchecks ; i++ )
   {
      auto v = s.sample() ;

      BOOST_REQUIRE( 
         (v >= -0.5) or 
         (v <= +0.5) ) ;
   }
}

BOOST_AUTO_TEST_CASE( testRandomReals )
{
   R3 s(-0.5, 0.5) ;

   testR3( s ) ;   

   for ( auto seed : {-0.5, -0.1, 0.3, 0.5} )
   {
      s.start( seed ) ;

      testR3( s ) ;
   }
}
