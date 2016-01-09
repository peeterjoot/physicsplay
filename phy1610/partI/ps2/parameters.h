/** \file parameters.h
 */
#if !defined phy1610_ps2_parameters_h_included
#define phy1610_ps2_parameters_h_included

#include "integers.h"

/// Physical parameters.
struct physical
{
   double  c      ;  //< wave speed
   double  tau    ;  //< damping time
   double  x1     ;  //< left most x value
   double  x2     ;  //< right most x value

   /**
     set physical parameters to some defaults
    */
   physical() ;
} ;

/// Simulation parameters
struct simulation
{
   double  runtime ;  //< how long should the simulation try to compute?
   double  dx     ;   //< spatial grid size

   /**
     set simulation parameters to some defaults
    */
   simulation() ;
} ;

/// Output parameters
struct output
{
   double  outtime ;   //< how often should a snapshot of the wave be written out? 
   bool    verbose ;   //< print output or just compute it?

   /**
     set output parameters to some defaults
    */
   output() ;
} ;

/// Derived parameters and parsing
struct parameters : public physical,simulation,output
{
   Uint   ngrid   ;  // number of x points
   Uint   npnts   ;  // number of x points including boundary points
   double dt      ;  // time step size
   Uint   nsteps  ;  // number of steps of that size to reach s.runtime
   Uint   nper    ;  // how many step s between snapshots

   /** 
      Read the parameter values from a file (argv[1]) if specified on the command line.
      If no file is specified, then the defaults are used.

      Compute the dependent parameters after the file is read (or skipped and the defaults used).
    */
   parameters( int argc, char* argv[] ) ;
} ;

#endif
