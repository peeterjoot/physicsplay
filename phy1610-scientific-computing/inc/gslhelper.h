/** \file gslhelper.h
 */
#if !defined phy1610_gslhelper_h_included
#define phy1610_gslhelper_h_included

#include <cassert>
#include <gsl/gsl_errno.h>
#include <gsl/gsl_min.h>
#include <gsl/gsl_roots.h>

/**
   Test for any return code that isn't one of GSL_CONTINUE or GSL_SUCCESS.
 */
inline bool isGslStatusFatal( int status )
{
   return ( (status != GSL_CONTINUE) && (status != GSL_SUCCESS) ) ;
}

/*
   gsl_root_test_delta deals with relative error in a (seemingly) smart way.  Such an error is
   usually defined as: e_r = |x - x_0|/|x|, so we want |x - x_0|/|x| < e_r for a desired e_r.
   That is problematic when the root is near zero.

   Instead this tests for relative error by checking that
      |x - x_0| < |x| e_r + e_a, where e_r is the desired relative error and e_a is the
   desired absolute error, so if the root is near zero, only the absolute error check
   will be relavant.

   However, testing shows that the use of gsl_root_test_delta with both absolute and relative
   errors specified simulateously can be error prone.  The following call demonstrates this:

      int status = gsl_root_test_delta( -12731.567231222018, -12730.345460737482, 1e-4, 1e-4) ;

   stepping into gsl_root_test_delta in the debugger (apt-get source gsl), I see:

      const double tolerance = epsabs + epsrel * fabs(x1)  ;

      if (fabs(x1 - x0) < tolerance || x1 == x0)
      (gdb) p fabs(x1 - x0)
      $6 = 1
      (gdb) p tolerance
      $7 = 1.2732567231222016

   This large valued (apparent) root, makes the relative error comparison come out
   indicating convergence, but that dwarfs the absolute error comparison which should have failed.
   We end up terminating the iteration prematurely, having not actually found the root.  Back
   substitution into the function shows that is the case.

   I think the gsl guys are trying to be too clever here combining the abs and rel error
   checks using a sum.  I think this should be too separate checks if both are supplied and
   GSL_SUCCESS only if both conditions are met separately.  Do this manually instead:
*/
inline int root_test_delta( const double x1, const double x2, const double abserr, const double relerr )
{
   int status ;

   if ( abserr == 0.0 )
   {
      assert( relerr != 0.0 ) ;

      status = gsl_root_test_delta( x1, x2, 0.0, relerr ) ;
   }
   else if ( relerr == 0.0 )
   {
      assert( abserr != 0.0 ) ;

      status = gsl_root_test_delta( x1, x2, abserr, 0.0 ) ;
   }
   else
   {
      status = gsl_root_test_delta( x1, x2, 0.0, relerr ) ;
      if ( status == GSL_SUCCESS )
      {
         status = gsl_root_test_delta( x1, x2, abserr, 0.0 ) ;
      }
   }

   return status ;
}

/**
   Like root_test_delta, test for the relative and absolute errors separately.
 */
inline int min_test_interval( const double x1, const double x2, const double abserr, const double relerr )
{
   int status ;

   if ( abserr == 0.0 )
   {
      assert( relerr != 0.0 ) ;

      status = gsl_min_test_interval( x1, x2, 0.0, relerr ) ;
   }
   else if ( relerr == 0.0 )
   {
      assert( abserr != 0.0 ) ;

      status = gsl_min_test_interval( x1, x2, abserr, 0.0 ) ;
   }
   else
   {
      status = gsl_min_test_interval( x1, x2, 0.0, relerr ) ;
      if ( status == GSL_SUCCESS )
      {
         status = gsl_min_test_interval( x1, x2, abserr, 0.0 ) ;
      }
   }

   return status ;
}

#endif
