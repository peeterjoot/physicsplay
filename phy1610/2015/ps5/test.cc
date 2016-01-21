/** \file test.cc

    Some unit tests.
 */
#include "ps5solver.h"
#include <iostream>

#define BOOST_TEST_MAIN
#define BOOST_TEST_MODULE test

#include "boosttest.h"

BOOST_AUTO_TEST_CASE( testsSolver )
{
   Uint maxIter = 100 ;
   const double err = 1e-4 ;

   ps5function f ;

   // The root is at 1.0, so this should adjust the upper bound of the interval higher:
   double x_min = 0.0 ;
   double x_max = 1.0 ;
   BOOST_REQUIRE( increaseIntervalIfNotBracketed( f, x_min, x_max, 10 ) == true && x_max > 1.0 ) ;

   std::cout << "[a,b] = " << "[ " << x_min << ", " << x_max << " ]" << std::endl ;

   {
      fdfSolver<ps5function> s( solver::newton ) ;

      fdfSolver<ps5function>::inputs p( ps5function::expectedRoot(), maxIter, err, err ) ;
      fdfSolver<ps5function>::results r ;

      s.iterate( p, r ) ;

      BOOST_REQUIRE( r.m_converged && fabs(r.m_x -ps5function::expectedRoot()) < err ) ;
   }
 
   {
      fSolver<ps5function> s( solver::falsepos ) ;

      fSolver<ps5function>::inputs p( 0, ps5function::expectedRoot(), maxIter, err, err ) ;
      fSolver<ps5function>::results r ;

      s.iterate( p, r ) ;

      BOOST_REQUIRE( r.m_converged && fabs(r.m_r -ps5function::expectedRoot()) < err ) ;
   }
}
