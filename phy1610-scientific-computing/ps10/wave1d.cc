//
// wave1d.cc - Simulates a one-dimensional damped wave equation modified
// to use pgplot for runtime display of solution with 1 second between frames.
//
// SciNet - March 2015
//
//
// https://support.scinet.utoronto.ca/education/go.php/176/content.php/cid/291/
//

#include <iostream>
#include <fstream>
#include <cmath>
#include <unistd.h>
#include <rarray>
#include <cpgplot.h>
#include "ticktock.h"
#include "inifile.h"
#include "farray.h"
#include "rangePartition.h"
#include <mpi.h>
#include <boost/assert.hpp>
#include <unistd.h>
#include "sendAndRecieveGhostCells.h"
#include "mpitask.h"
#include "iohandler.h"

int main( int argc, char* argv[] )
{
   //mpitask mpi( 1, 2 ) ;
   //mpitask mpi( 3, 4 ) ;
   mpitask mpi( &argc, &argv ) ;

   // Open inifile and parse (using Inifile class from inifile.h)
   Inifile parameter( argc==1 ? "default.txt" : argv[1] ) ;

   // Physical parameters
   const double         c        = parameter.get<double>( "c", 1.0 ) ;    // wave speed
   const double         tau      = parameter.get<double>( "tau", 20.0 ) ;  // damping time
   const double         x1       = parameter.get<double>( "x1", -26.0 ) ;  // left most x value
   const double         x2       = parameter.get<double>( "x2", +26.0 ) ;  // right most x value

   // Simulation parameters
   const double         runtime  = parameter.get<double>( "runtime", 50.0 ) ;   // how long should the simulation try to compute?
   const double         dx       = parameter.get<double>( "dx", 0.01 ) ;      // spatial grid mpi.m_size  //0.02

   // Output parameters
   const double         outtime  = parameter.get<double>( "outtime", 1.0 ) ; // how often should a snapshot of the wave be written out?

   const int            graphics = parameter.get<int>( "graphics", -1 ) ;   // output to graphics (with 1 sec delay)

   // Output file name
   const std::string    dataFilename  = parameter.get<std::string>( "outfilebasename", "dataFilename" ) ;   // 

   const bool           ioenabled = parameter.get<bool>( "ioenabled", 0 ) ;   // output to a file (not attempted if graphics enabled)

   // Derived parameters
   const int    ngrid   = (x2-x1)/dx ;  // number of x points
   const double dt      = 0.5*dx/c ;    // time step mpi.m_size
   const int    nsteps  = runtime/dt ;  // number of steps of that mpi.m_size to reach runtime
   const int    nper    = outtime/dt ;  // how many step s between snapshots

   // Report all the values.
   std::cout << "#c         " << c       << std::endl ;
   std::cout << "#tau       " << tau     << std::endl ;
   std::cout << "#x1        " << x1      << std::endl ;
   std::cout << "#x2        " << x2      << std::endl ;
   std::cout << "#runtime   " << runtime << std::endl ;
   std::cout << "#dx        " << dx      << std::endl ;
   std::cout << "#outtime   " << outtime << std::endl ;
   std::cout << "#ngrid     " << ngrid   << std::endl ;
   std::cout << "#dt        " << dt      << std::endl ;
   std::cout << "#nsteps    " << nsteps  << std::endl ;
   std::cout << "#nper      " << nper    << std::endl ;
   std::cout << "#graphics  " << graphics << std::endl ;
   std::cout << "#ioenabled " << int(ioenabled) << std::endl ;

   rangePartition partition( ngrid, mpi.m_size, mpi.m_rank ) ;
   auto pgrid{ partition.localPartitionSize() } ;
   auto npnts{ pgrid + 2 } ;
   std::cout << "#pgrid " << int(pgrid) << std::endl ;
   std::cout << "#npnts " << int(npnts) << std::endl ;

   // Define and allocate arrays.
   farray rho_prev(npnts) ; // time step t-1
   farray rho(npnts) ;      // time step t
   farray rho_next(npnts) ; // time step t+1
   farray rho_init(npnts) ; // initial values
   farray x(npnts) ;        // x values

   // Set zero dirichlet boundary conditions for the global domain.  If one or more of the end points are ghost cells 
   // in a mpi.m_size>1 mpirun, then the ghost-cell boundary values will be filled in properly when rho[] is initialized
   // below
   rho.fill( 0.0 ) ;
   rho_prev.fill( 0.0 ) ;
   rho_next.fill( 0.0 ) ;

   // Initialize.
   auto fullrange{ partition.subsetOfGlobalRangeInThisPartition( 1, ngrid ) } ;
   // Example: mpi.m_rank=0 we map [1,10] (say) to [0,11]
   for ( auto j{fullrange.first-1} ; j <= (fullrange.second + 1) ; j++ )
   {
      auto i{ partition.toLocalDomain( j ) } ;

      x[i] = x1 + (((int)j-1)*(x2-x1))/ngrid ;
   }

   auto global_npnts{ ngrid + 2 } ;

   // Excite.
   auto waverange{ partition.subsetOfGlobalRangeInThisPartition( global_npnts/4 + 1, 3*global_npnts/4 - 1 ) } ;
   if ( waverange != partition.emptySubRange() )
   {
      for ( auto j{ waverange.first-1} ; j <= (waverange.second +1) ; j++ )
      {
         auto i{ partition.toLocalDomain( j ) } ;

         rho[i] = 0.25 - fabs( float((int)j-global_npnts/2) / float(global_npnts) ) ;
         rho_prev[i] = rho[i] ;
         rho_init[i] = rho[i] ;
      }
   }

   using iocfg = iohandler::cfg ;
   iocfg cfg = iocfg::noop ;

   if ( graphics == mpi.m_rank )
   {
      cfg = iocfg::graphics ;
   }
   else if ( ioenabled )
   {
      cfg = iocfg::ascii ;
   }
   else
   {
      // cfg = iocfg::netcdf ;
   }

   iohandler io( cfg, dataFilename, ngrid, mpi.m_rank ) ;
   io.writeMeta( partition.m_myFirstGlobalElementIndex -1,
                 partition.localPartitionSize(),
                 &x[1],
                 &rho_init[1] ) ;

   const double laplacianScaleFactor{ pow( c/dx, 2 ) * dt } ;
   const double invTau{ 1/tau } ;

   // measure time
   TickTock tt ;
   tt.tick() ;

   // Take timesteps
   for ( int s{1} ; s <= nsteps ; s++ )
   {
      // Evolve
      // \partial_{tt} u - c^2 \partial_{xx} u + \inv{\tau} \partial_t u = 0
      for ( auto j{fullrange.first} ; j <= fullrange.second ; j++ )
      {
         auto i { partition.toLocalDomain( j ) } ;

         float laplacianTimesDt = laplacianScaleFactor * ( rho[i+1] + rho[i-1] - 2 * rho[i] ) ;
         float friction         = ( rho[i] - rho_prev[i] ) * invTau ;

         rho_next[i] = 2 * rho[i] - rho_prev[i] + dt * ( laplacianTimesDt - friction ) ;
      }

      if ( mpi.m_size > 1 )
      {
         float newLeftGhostCell, newRightGhostCell ;
         sendAndRecieveGhostCells( rho_next[1], rho_next[ pgrid ],
                                   &newRightGhostCell, &newLeftGhostCell,
                                   mpi.m_size,
                                   mpi.m_rank ) ;
         //std::cout << "#debug: " << mpi.m_rank << "( " << rho_next[1] << ", " << rho_next[pgrid] << " ): " << newLeftGhostCell << ", " << newRightGhostCell << '\n' ;
         rho_next[0]       = newLeftGhostCell ;
         rho_next[pgrid+1] = newRightGhostCell ;
      }
      
      // Rotate array pointers so t+1 becomes the new t etc.
      farray temp ;
      temp     = rho_prev ;
      rho_prev = rho ;
      rho      = rho_next ;
      rho_next = temp ;
	
      //Output every nper
      if ( s % nper == 0 )
      {
         io.writeData( s,
                       partition.m_myFirstGlobalElementIndex -1,
                       partition.localPartitionSize(),
                       &x[1],
                       &rho_init[1] ) ;
      }
   }

   // Output measured runtime.
   std::cout << "#Walltime = " << tt.silent_tock() << " sec."  << std::endl ;

   return 0 ;
}
