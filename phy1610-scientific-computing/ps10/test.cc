/**
   \file test.cc

   standalone simple test cases.
 */
#define BOOST_TEST_MAIN
#define BOOST_TEST_MODULE test

#include "boosttest.h"
#include "myexceptions.h"
#include "rangePartition.h"
#include <vector>

BOOST_AUTO_TEST_CASE( partitionTest1 )
{
   constexpr auto size{4} ;

   for ( auto extra{0} ; extra < 3 ; extra++ )
   {
      auto N{40 + extra} ;

      using s = rangePartition::subrange ;

      s expected[] { {1, 10}, {11, 20}, {21, 30}, {31, N} } ;

      // partition [1,41] into [1,10]
      for ( auto rank{0} ; rank < size ; rank++ )
      {
         rangePartition r( N, size, rank ) ;

         s sub{ r.subsetOfGlobalRangeInThisPartition(1, N) } ;

         BOOST_REQUIRE( sub == expected[rank] ) ;
         BOOST_REQUIRE( r.toLocalDomain( sub.first ) == 1 ) ;

         if ( rank == (size-1) )
         {
            BOOST_REQUIRE( r.toLocalDomain( sub.second ) == (rangePartition::index_type)(10 + extra) ) ;
         }
         else
         {
            BOOST_REQUIRE( r.toLocalDomain( sub.second ) == 10 ) ;
         }
      }
   }
}
