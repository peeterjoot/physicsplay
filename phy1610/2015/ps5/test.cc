/** \file test.cc

    Some unit tests.
 */
#include "ps5solver.h"
#include "squareRootTwoFunction.h"
#include <iostream>

#define BOOST_TEST_MAIN
#define BOOST_TEST_MODULE test

#include "boosttest.h"

const Uint maxIter = 100 ;
const Uint maxSubDivisions = 4 ;
const Uint maxExpansionIters = 4 ;
const double err = 1e-4 ;

BOOST_AUTO_TEST_CASE( testsSolver )
{
   ps5function f ;

   // The root is at 1.0, so this should adjust the upper bound of the interval higher:
   double x_min = 0.0 ;
   double x_max = 1.0 ;
   BOOST_REQUIRE( increaseIntervalIfNotBracketed( f, x_min, x_max, 10 ) == true && (x_max > 1.0) && (f(x_min) * f(x_max) < 0.0) ) ;

   // test when the bracket has an upper bound on the root, and when the bracket doesn't contain the
   // root (the bracket expansion code should deal with the latter).
   //
   for ( auto u : {ps5function::expectedRoot()/2, ps5function::expectedRoot()} )
   {
      {
         fdfSolver<ps5function> s( solver::newton ) ;

         derivativeIterationInputs p( u, maxIter, err, err ) ;
         derivativeIterationResults r ;

         s.iterate( p, r ) ;

         BOOST_REQUIRE( r.m_converged &&
                        ((fabs(r.m_x - ps5function::expectedRoot()) < err) ||
                         (fabs(r.m_x + ps5function::expectedRoot()) < err)) ) ;
      }

      {
         fdfSolver<ps5function> s( solver::newton ) ;

         intervalIterationInputs p( 0, u, maxIter, maxExpansionIters, maxSubDivisions, err, err ) ;
         intervalIterationResults r ;

         s.iterateBracketed( p, r ) ;

         BOOST_REQUIRE( r.m_converged &&
                        ((fabs(r.m_x - ps5function::expectedRoot()) < err) ||
                         (fabs(r.m_x + ps5function::expectedRoot()) < err)) ) ;
      }

      {
         fSolver<ps5function> s( solver::falsepos ) ;
         intervalIterationInputs p( 0, u, maxIter, maxExpansionIters, maxSubDivisions, err, err ) ;
         intervalIterationResults r ;

         s.iterate( p, r ) ;

         BOOST_REQUIRE( r.m_converged &&
                        ((fabs(r.m_x - ps5function::expectedRoot()) < err) ||
                         (fabs(r.m_x + ps5function::expectedRoot()) < err)) ) ;
      }
   }
}

BOOST_AUTO_TEST_CASE( testsSquareRootTwo )
{
   squareRootTwoFunction f ;

   // The root is at 1.41, so this decrease the bounds to find an interval that find a sign change bracket.
   {
      double x_min = -2.0 ;
      double x_max = 2.0 ;
      bool foundOne = decreaseIntervalIfNotBracketed( f, x_min, x_max, 10 ) ;
      BOOST_REQUIRE( foundOne == true ) ;
      BOOST_REQUIRE( f(x_min) * f(x_max) < 0.0 ) ;
   }

   {
      fdfSolver<squareRootTwoFunction> s( solver::newton ) ;

      intervalIterationInputs p( -2.0, 2.0, maxIter, maxExpansionIters, maxSubDivisions, err, err ) ;
      intervalIterationResults r ;

      s.iterateBracketed( p, r ) ;

      BOOST_REQUIRE( r.m_converged &&
                     ((fabs(r.m_x - squareRootTwoFunction::expectedRoot()) < err) ||
                      (fabs(r.m_x + squareRootTwoFunction::expectedRoot()) < err)) ) ;
   }
 }
