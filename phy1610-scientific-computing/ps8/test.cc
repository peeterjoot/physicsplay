/**
   \file test.cc

   standalone simple test cases.
 */
#define BOOST_TEST_MAIN
#define BOOST_TEST_MODULE test

#include "boosttest.h" // include this first to override assert()
#include "randomgenerators.h"
#include "banded.h"
#include "myexceptions.h"
#include <iostream>
#include <string>

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
}

BOOST_AUTO_TEST_CASE( banded )
{
   auto n{6} ;
   auto nm{5} ;
   darray2 m( n, n ) ;
   darray2 compare( n, n ) ;

   compare.fill( 0.0 ) ;
   int r{0} ;
   compare[r][0] = 2 ; compare[r][1] = 3 ; compare[r][5] = 1 ; r++ ;
   compare[r][1] = 2 ; compare[r][2] = 3 ; compare[r][0] = 1 ; r++ ;
   compare[r][2] = 2 ; compare[r][3] = 3 ; compare[r][1] = 1 ; r++ ;
   compare[r][3] = 2 ; compare[r][4] = 3 ; compare[r][2] = 1 ; r++ ;
   compare[r][4] = 2 ; compare[r][5] = 3 ; compare[r][3] = 1 ; r++ ;
   compare[r][5] = 2 ; compare[r][0] = 3 ; compare[r][4] = 1 ; r++ ;

   initializeBandedMatrix( m, 1, 2, 3, BANDING_TYPE::CYCLIC ) ;

   BOOST_REQUIRE( std::equal( &m[0][0], &m[nm][nm] + 1, &compare[0][0] ) ) ;

   compare[nm][0] = 0 ;
   compare[0][nm] = 0 ;

   initializeBandedMatrix( m, 1, 2, 3, BANDING_TYPE::TRIDIAGONAL ) ;

   BOOST_REQUIRE( std::equal( &m[0][0], &m[nm][nm] + 1, &compare[0][0] ) ) ;

   darray2 mbyn( n, n-1 ) ;
   BOOST_CHECK_THROW( initializeBandedMatrix( mbyn, 1, 2, 3, BANDING_TYPE::TRIDIAGONAL ), array_not_square_error ) ;
}
