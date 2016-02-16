#define BOOST_TEST_MAIN
#define BOOST_TEST_MODULE test

#include "boosttest.h"
#include "integers.h"
#include "myrarray2.h"
#include "ants_on_table.h"
#include <stdio.h>

template <typename atype>
void testArray( const char * const what )
{
   constexpr auto eps = 1e-4 ;
   char buf[ 128 ] ;
   atype a( 4 ) ;
   atype b( 4, 3.14 ) ;
   double t1, t2 ;

   a.fill( 3.14 ) ;

   a.add( 2, 3, 1.0 ) ;
   b.add( 2, 3, 1.0 ) ;

   a.assign( 1, 1, 4.0 ) ;
   b.assign( 1, 1, 4.0 ) ;

   BOOST_REQUIRE( a( 1, 1 ) == 4.0 ) ;

   double sum = 0.0 ;

   for ( Uint i = 0 ; i < 4 ; i++ )
   {
      for ( Uint j = 0 ; j < 4 ; j++ )
      {
         t1 = a( i, j ) ;
         t2 = b( i, j ) ;
         snprintf( buf, sizeof(buf), "%s:i,j=%u,%u: a(i,j) = %f, b(i,j) = %f\n", what, (unsigned)i, (unsigned)j, t1, t2 ) ;
         BOOST_REQUIRE( a( i, j ) == b( i, j ),  ) ;

         sum += a( i, j ) ;
      }
   }

   t1 = a.sum() ;
   snprintf( buf, sizeof(buf), "%s: manual sum: %f, a.sum: %f\n", what, sum, t1 ) ;
   BOOST_REQUIRE_MESSAGE( abs(sum == a.sum()) < eps, buf ) ;

   t1 = b.sum() ;
   snprintf( buf, sizeof(buf), "%s: sum: %f, a.sum: %f\n", what, sum, t1 ) ;
   BOOST_REQUIRE_MESSAGE( abs(sum == b.sum()) < eps, buf ) ;
}

BOOST_AUTO_TEST_CASE( myra )
{
   testArray< vecarray2 >( "vecarray" ) ;
   testArray< valarray2 >( "valarray" ) ;
   testArray< farray2 >( "farray" ) ;
   testArray< rarray2 >( "rarray" ) ;
}

BOOST_AUTO_TEST_CASE( timestep )
{
   // test ants bounds checks in a few size/number-of-iteration configurations:

   for ( auto tableGridSize : { 2, 11, 51, 101, 402, 803 } )
   {
      ants_on_table ants( tableGridSize ) ;

      for ( auto initialNumberOfAnts : { 1, 21, 431, 1271 } )
      {
         for ( auto numberOfTimeIntervals : { 0, 1, 5, 11, 23, 101 } )
         {
            // 
            // Attempting to verify a 1x1 boundary case failed (infinite loop).  That's because the 
            // initialization algorithm can't handle that small of a grid size (the sine computed
            // is always zero).  Omitting that test, and adding an assert into the ants_on_table
            // constructor instead.
            //
            ants.initialize( initialNumberOfAnts ) ;

            float lastTotal = ants.total_number_of_ants() ;
            BOOST_REQUIRE( lastTotal == initialNumberOfAnts ) ;

            for ( int i = 0 ; i < numberOfTimeIntervals ; i++ )
            {
               float total = ants.total_number_of_ants() ;

               // check for spontaneous generation of ants compared previous timestep:
               BOOST_REQUIRE( total <= lastTotal ) ;

               lastTotal = total ;

               // check for spontaneous generation of ants compared to initial value:
               BOOST_REQUIRE( lastTotal <= initialNumberOfAnts ) ;

               // make sure that the number of ants doesn't ever go negative
               BOOST_REQUIRE( lastTotal >= 0 ) ;

               ants.timestep() ;
            }
         }
      }
   }
}
