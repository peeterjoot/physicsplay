/**
   \file solver.cc
 */

#include <new>
#include <iostream>
#include <gsl/gsl_math.h>
#include <gsl/gsl_errno.h>
#include <stdio.h>
#include <cmath>
#include <cassert>
#include "integers.h"
#include "solver.h"
#include "gslhelper.h"

template <class paramType>
fSolver<paramType>::fSolver( paramType & p ) : m_T( gsl_root_fsolver_brent ), m_params{p}
{
   m_F.function = paramType::function ;
   m_F.params = &m_params ;

   // turn off the print and abort on error behavior
   gsl_set_error_handler_off() ;

   m_s = gsl_root_fsolver_alloc( m_T ) ;
   if ( !m_s )
   {
      throw std::bad_alloc() ;
   }
}

template <class paramType>
fSolver<paramType>::~fSolver()
{
   gsl_root_fsolver_free( m_s ) ;
}

template <class paramType>
void fSolver<paramType>::iterate( const intervalIterationInputs & p, intervalIterationResults & r )
{
   r.m_xLo        = p.m_xLo ;
   r.m_xHi        = p.m_xHi ;
   r.m_x          = p.m_xLo ;

   r.m_status     = gsl_root_fsolver_set( m_s, &m_F, r.m_xLo, r.m_xHi ) ;
   r.m_solvername = gsl_root_fsolver_name( m_s ) ;

   if ( !r.m_status )
   {
      if ( p.m_verbose )
      {
         printf( "%5s [%9s, %9s] %9s %10s %9s\n",
                 "iter", "lower", "upper", "root", "err", "err(est)" ) ;
      }

      do {
         r.m_iter++ ;

         r.m_status = gsl_root_fsolver_iterate( m_s ) ;
         if ( isGslStatusFatal( r.m_status ) )
         {
            break ;
         }

         r.m_x = gsl_root_fsolver_root( m_s ) ;

         r.m_xLo = gsl_root_fsolver_x_lower( m_s ) ;
         r.m_xHi = gsl_root_fsolver_x_upper( m_s ) ;

         // avoiding simulaneous absolute and relative error checks as with the fdf solver iteration
         // (see comments above)
         r.m_status = gsl_root_test_interval( r.m_xLo, r.m_xHi, 0.0, p.m_relerr ) ;
         if ( isGslStatusFatal( r.m_status ) )
         {
            break ;
         }
         else if ( r.m_status == GSL_SUCCESS )
         {
            r.m_status = gsl_root_test_interval( r.m_xLo, r.m_xHi, p.m_abserr, 0.0 ) ;
            if ( isGslStatusFatal( r.m_status ) )
            {
               break ;
            }
         }

         if ( p.m_verbose )
         {
            printf( "%5d [%.7f, %.7f] %.7f %.7f\n",
                    (int)r.m_iter, r.m_xLo, r.m_xHi, r.m_x, r.m_xHi - r.m_xLo ) ;
         }

      } while ( (r.m_status == GSL_CONTINUE) && (r.m_iter < p.m_max_iter) ) ;

      if ( r.m_status == GSL_SUCCESS )
      {
         r.m_converged = true ;
      }
   }

   r.m_strerror = gsl_strerror( r.m_status ) ;
}
