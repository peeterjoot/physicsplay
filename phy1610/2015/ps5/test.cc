/** \file test.cc

    Some unit tests.
 */
#include "mysolver.cc"
#include "ps5function.h"

#define BOOST_TEST_MAIN
#define BOOST_TEST_MODULE test

#include "boosttest.h"

BOOST_AUTO_TEST_CASE( testsSolver )
{
   fSolver<ps5function> sb( solver::brent ) ;

   // The root is at 1.0, so this should adjust the upper bound of the interval higher:
   double x_min = 0.0 ;
   double x_max = 1.0 ;
   BOOST_REQUIRE( sb.increaseIntervalIfNotBracketed( x_min, x_max, 10 ) == true && x_max > 1.0 ) ;

   std::cout << "[a,b] = " << "[ " << x_min << ", " << x_max << " ]" << std::endl ;

   fdfSolver<ps5function> sn( solver::newton ) ;

   sn.iterate( ps5function::expectedRoot(), 100, 1e-4 ) ;

   fSolver<ps5function> sf( solver::falsepos ) ;

   sn.iterate( 0, ps5function::expectedRoot(), 100, 1e-4 ) ;
}
