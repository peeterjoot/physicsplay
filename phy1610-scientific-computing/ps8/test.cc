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

BOOST_AUTO_TEST_CASE( testFairCoin )
{
   using FairCoin = RandomIntegers<-1, 2, 1> ;

   FairCoin c ;

   for ( auto i = 0 ; i < Nchecks ; i++ )
   {
      auto v = c.sample() ;

      BOOST_REQUIRE( (v == -1) or (v == +1) ) ;
   }
}

inline bool equals( const double v1, const double v2 )
{
   constexpr auto tolerance{ 1e-8 } ;

   return std::abs( v1 - v2 ) < tolerance ;
}

BOOST_AUTO_TEST_CASE( integer )
{
   RandomDiscreteReals<2> r(-0.5, 0.5) ;

   for ( auto i = 0 ; i < Nchecks ; i++ )
   {
      auto v = r.sample() ;

      BOOST_REQUIRE_MESSAGE(
         equals( v, -0.5 ) or 
         equals( v, +0.5 ) or 
         equals( v, 0 ), "v = " + std::to_string(v) ) ;
   }
}

BOOST_AUTO_TEST_CASE( openStreamWriteExceptionTest )
{
   RandomReals<> s(-0.5, 0.5) ;

   for ( auto i = 0 ; i < Nchecks ; i++ )
   {
      auto v = s.sample() ;

      BOOST_REQUIRE( 
         (v >= -0.5) or 
         (v <= +0.5) ) ;
   }
}
