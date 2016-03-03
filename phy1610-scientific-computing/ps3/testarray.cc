#define BOOST_TEST_MAIN
#define BOOST_TEST_MODULE test

#include "boosttest.h"
#include "integers.h"
#include "myrarray2.h"
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
         BOOST_REQUIRE_MESSAGE( a( i, j ) == b( i, j ), buf ) ;

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
   testArray< vecarray2<float> >( "vecarray" ) ;
   testArray< farray2<float> >( "farray" ) ;
   testArray< valarray2<float> >( "valarray" ) ;
   testArray< rarray2<float> >( "rarray" ) ;
}
