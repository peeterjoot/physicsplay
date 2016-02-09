#define BOOST_TEST_MAIN
#define BOOST_TEST_MODULE test

#include "boosttest.h"
#include "ants_on_table.h"

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
