/**
   \file wave1d.cc

   Simulates a one-dimensional damped wave equation
  
   \author Ramses van Zon - January 2015
 */

#include <iostream>
#include <fstream>
#include <cmath>
#include <memory>
#include <vector>

/// Physical parameters.
struct physical
{
   double  c      ;  //< wave speed
   double  tau    ;  //< damping time
   double  x1     ;  //< left most x value
   double  x2     ;  //< right most x value

   physical()
   {
      c      =   1.0;  
      tau    =  20.0;  
      x1     = -26.0;  
      x2     = +26.0;  
   }
} ;

/// Simulation parameters
struct simulation
{
   double  runtime ;  //< how long should the simulation try to compute?
   double  dx     ;   //< spatial grid size

   simulation()
   {
      runtime = 200.0;
      dx     = 0.02;
   }
} ;

/// Output parameters
struct output
{
   double  outtime ;   //< how often should a snapshot of the wave be written out? 
   bool    verbose ;   //< print output or just compute it?

   output()
   {
      outtime = 1.0;
      verbose = true ;
   }
} ;

/// Derived parameters and parsing
struct parameters : public physical,simulation,output
{
   int    ngrid   = (x2-x1)/dx;  // number of x points
   int    npnts   = ngrid + 2;   // number of x points including boundary points
   double dt      = 0.5*dx/c;   // time step size
   int    nsteps  = runtime/dt;  // number of steps of that size to reach s.runtime
   int    nper    = outtime/dt;  // how many step s between snapshots

   parameters( int argc, char* argv[] )
   {
      // Read the values from a file if specified on the command line
      if (argc > 1) {
         std::ifstream infile(argv[1]);
         infile >> c;
         infile >> tau;
         infile >> x1;
         infile >> x2;
         infile >> runtime;
         infile >> dx;
         infile >> outtime;
         infile >> verbose;
         infile.close();
      }

      ngrid   = (x2-x1)/dx;  // number of x points
      npnts   = ngrid + 2;   // number of x points including boundary points
      dt      = 0.5*dx/c;    // time step size
      nsteps  = runtime/dt;  // number of steps of that size to reach s.runtime
      nper    = outtime/dt;  // how many step s between snapshots

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
                   << "#nper    " << nper    << std::endl;
      }
   }
} ;

class wave1d
{
   std::vector<double> rho_prev ; // time step t-1
   std::vector<double> rho      ; // time step t
   std::vector<double> rho_next ; // time step t+1
   std::vector<double> x        ; // x values
   const parameters & p ;

public:
   wave1d( const parameters & p_ ) :
      rho_prev(),
      rho(),
      rho_next(),
      x(),
      p(p_)
   {
      rho_prev.resize( p.npnts, 0.0 ) ;
      rho.resize( p.npnts, 0.0 ) ;
      rho_next.resize( p.npnts, 0.0 ) ;
      x.resize( p.npnts, 0.0 ) ;
   }

   ~wave1d()
   {
   }

   void initializeAndExcite()
   {
      // Initialize
      for (int i = 0; i < p.npnts; i++) {
         x[i] = p.x1 + ((i-1)*(p.x2-p.x1))/p.ngrid; 

         // resize does this, since the fill value was specified.
         //rho[i] = 0.0;
         //rho_prev[i] = 0.0;
         //rho_next[i] = 0.0;
      }

      // Excite
      for (int i = p.npnts/4 + 1; i < 3*p.npnts/4; i++) {
         rho[i] = 0.25 - fabs(double(i-p.npnts/2)/double(p.npnts));
         rho_prev[i] = rho[i];
      }
   }

   /**
      Show the state of the computation.

      \param time [in]
         N * dt at the time of the display.
     */
   void display( double time )
   {
      std::cout << "# t = " << time << "\n";
      for (int i = 1; i <= p.ngrid; i++) 
         std::cout << x[i] << " " << rho[i] << "\n";
   }

   void compute()
   {
      // Take timesteps
      for (int s = 0; s < p.nsteps; s++) {

         // Set zero dirichlet boundary conditions
         rho[0] = 0.0;
         rho[p.ngrid+1] = 0.0;

         // Evolve
         for (int i = 1; i <= p.ngrid; i++) {
            double laplacian = pow(p.c/p.dx,2)*(rho[i+1] + rho[i-1] - 2*rho[i]);
            double friction = (rho[i] - rho_prev[i])/p.tau;
            rho_next[i] = 2*rho[i] - rho_prev[i] + p.dt*(laplacian*p.dt-friction);
         }

         // Rotate array pointers so t+1 becomes the new t etc.
         // Note that vector::swap doesn't touch the elements themselves, just
         // the vector metadata.
         std::vector<double> temp ;
         temp    .swap( rho_prev ) ;
         rho_prev.swap( rho ) ;
         rho     .swap( rho_next ) ;
         rho_next.swap( temp ) ;

         // Output density
         if ( ((s+1)%p.nper == 0) && p.verbose ) {
            display( s * p.dt ) ;
         }
      }

//      if ( p.verbose ) {
//         display( (p.nsteps -1) * p.dt ) ;
//      }
   }
} ;

int main(int argc, char* argv[])
{
   parameters p( argc, argv ) ;

   wave1d w( p ) ;

   w.initializeAndExcite() ;

   if ( p.verbose )
   {
      // Output initial signal
      w.display( 0.0 ) ;
   }
   w.compute() ;

   return 0;
}
