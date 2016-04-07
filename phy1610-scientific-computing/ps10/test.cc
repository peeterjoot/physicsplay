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

using s = rangePartition::subrange ;
s empty = rangePartition::emptySubRange() ;

BOOST_AUTO_TEST_CASE( partitionTest1 )
{
   constexpr auto size{4} ;

   for ( auto extra{0} ; extra < 3 ; extra++ )
   {
      auto N{40 + extra} ;

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

BOOST_AUTO_TEST_CASE( partitionTest2 )
{
   constexpr auto size{4} ;
   constexpr auto N{41} ;

   {
      constexpr auto rank{0} ; // partition gets [1,10]

      constexpr auto NTC{5} ;
      s input[NTC]    { {1, 20}, {1, 10}, {5,10}, {5,15}, {20, N} } ;
      s expected[NTC] { {1, 10}, {1, 10}, {5,10}, {5,10}, empty } ;

      rangePartition r( N, size, rank ) ;

      for ( auto i{0} ; i < NTC ; i++ )
      {
         s sub{ r.subsetOfGlobalRangeInThisPartition( input[i].first, input[i].second ) } ;

         BOOST_REQUIRE( sub == expected[i] ) ;
      }
   }

   {
      constexpr auto rank{1} ; // partition gets [11,20]

      constexpr auto NTC{6} ;
      s input[NTC]    { {1, 10}, {5, 10}, {5, 15},  {10, 20}, {20, N}, {21, N} } ;
      s expected[NTC] { empty,   empty,   {11, 15}, {11, 20}, {20,20}, empty } ;

      rangePartition r( N, size, rank ) ;

      for ( auto i{0} ; i < NTC ; i++ )
      {
         s sub{ r.subsetOfGlobalRangeInThisPartition( input[i].first, input[i].second ) } ;

         BOOST_REQUIRE( sub == expected[i] ) ;
      }
   }

   {
      constexpr auto rank{3} ; // partition gets [30,41]

      constexpr auto NTC{7} ;
      s input[NTC]    { {1, 10}, {5, 10}, {5, 15},  {10, 20}, {20, N}, {31, N}, {29, 40} } ;
      s expected[NTC] { empty,   empty,   empty,    empty,    {31, N}, {31, N}, {31, 40} } ;

      rangePartition r( N, size, rank ) ;

      for ( auto i{0} ; i < NTC ; i++ )
      {
         s sub{ r.subsetOfGlobalRangeInThisPartition( input[i].first, input[i].second ) } ;

         BOOST_REQUIRE( sub == expected[i] ) ;
      }
   }
}
