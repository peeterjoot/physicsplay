/** \file parameters.cc
 */
#include <fstream>
#include <iostream>
#include "parameters.h"

physical::physical() :
   c{ 1.0 },
   tau{ 20.0 },
   x1{ -26.0 },
   x2{ +26.0 }
{
}

simulation::simulation() :
   runtime{ 200.0 },
   dx{ 0.02 }
{
}

output::output() :
   outtime{ 1.0 },
   verbose{ true }
{
}

parameters::parameters( int argc, char* argv[] )
{
   // Read the values from a file if specified on the command line
   if (argc > 1) {
      std::ifstream infile(argv[1]) ;
      infile >> c ;
      infile >> tau ;
      infile >> x1 ;
      infile >> x2 ;
      infile >> runtime ;
      infile >> dx ;
      infile >> outtime ;
      infile >> verbose ;
      infile.close() ;
   }

   ngrid   = (x2-x1)/dx ;  // number of x points
   npnts   = ngrid + 2 ;   // number of x points including boundary points
   dt      = 0.5*dx/c ;    // time step size
   nsteps  = runtime/dt ;  // number of steps of that size to reach s.runtime
   nper    = outtime/dt ;  // how many step s between snapshots

   // Report all the values
   if ( verbose )
   {
      std::cout << "#c       " << c       << "\n"
                << "#tau     " << tau     << "\n"
                << "#x1      " << x1      << "\n"
                << "#x2      " << x2      << "\n"
                << "#runtime " << runtime << "\n"
                << "#dx      " << dx      << "\n"
                << "#outtime " << outtime << "\n"
                << "#ngrid   " << ngrid   << "\n"
                << "#dt      " << dt      << "\n"
                << "#nsteps  " << nsteps  << "\n"
                << "#nper    " << nper    << std::endl ;
   }
}
