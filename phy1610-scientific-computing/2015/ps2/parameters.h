/** \file parameters.h
 */
#if !defined phy1610_ps2_parameters_h_included
#define phy1610_ps2_parameters_h_included

#include "integers.h"

#define Sint32 int
/// Physical parameters.
struct physical
{
   double c{ 1.0 }    ;  ///< wave speed
   double tau{ 20.0 } ;  ///< damping time
   double x1{ -26.0 } ;  ///< left most x value
   double x2{ +26.0 } ;  ///< right most x value
} ;

/// Simulation parameters
struct simulation
{
   double  runtime{ 200.0 } ;  ///< how long should the simulation try to compute?
   double  dx     { 0.02 }  ;  ///< spatial grid size
} ;

/// Output parameters
struct output
{
   double  outtime{ 1.0 } ;    ///< how often should a snapshot of the wave be written out?
   bool    verbose{ true } ;   ///< print output or just compute it?
} ;

/// Derived parameters and parsing
struct parameters : public physical,simulation,output
{
   Sint32   ngrid   ;  ///< number of x points
   Sint32   npnts   ;  ///< number of x points including boundary points
   double   dt      ;  ///< time step size
   Sint32   nsteps  ;  ///< number of steps of that size to reach runtime
   Sint32   nper    ;  ///< how many step s between snapshots

   /**
      Read the parameter values from a file (argv[1]) if specified on the command line.
      If no file is specified, then the defaults are used.

      Compute the dependent parameters after the file is read (or skipped and the defaults used).
    */
   parameters( int argc, char* argv[] ) ;
} ;

#endif
