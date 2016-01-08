/**
   \file wave1d.cc

   Simulates a one-dimensional damped wave equation
  
   \author Ramses van Zon - January 2015
 */

#include <iostream>
#include <fstream>
#include <cmath>
#include <memory>
#include <array>

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

   output()
   {
      outtime =  1.0;
   }
} ;

int main(int argc, char* argv[])
{
   physical p ;
   simulation s ;
   output o ;

   // Read the values from a file if specified on the command line
   if (argc > 1) {
      std::ifstream infile(argv[1]);
      infile >> p.c;
      infile >> p.tau;
      infile >> p.x1;
      infile >> p.x2;
      infile >> s.runtime;
      infile >> s.dx;
      infile >> o.outtime;
      infile.close();
   }

   // Derived parameters
   int    ngrid   = (p.x2-p.x1)/s.dx;  // number of x points
   int    npnts   = ngrid + 2;   // number of x points including boundary points
   double  dt     = 0.5*s.dx/p.c;   // time step size
   int    nsteps  = s.runtime/dt;  // number of steps of that size to reach s.runtime
   int    nper   = o.outtime/dt;  // how many step s between snapshots

   // Report all the values
   std::cout << "#c      " << p.c      << std::endl;
   std::cout << "#tau    " << p.tau    << std::endl;
   std::cout << "#x1     " << p.x1     << std::endl;
   std::cout << "#x2     " << p.x2     << std::endl;
   std::cout << "#runtime " << s.runtime << std::endl;
   std::cout << "#dx     " << s.dx     << std::endl;
   std::cout << "#outtime " << o.outtime << std::endl; 
   std::cout << "#ngrid   " << ngrid   << std::endl;
   std::cout << "#dt     " << dt     << std::endl;
   std::cout << "#nsteps  " << nsteps  << std::endl;   
   std::cout << "#nper   " << nper   << std::endl;

   using values = std::array<double, npnts> ;
   using valuePointer = std::unique_ptr< values > ;

   // Define and allocate arrays, deallocated when the pointers go out of scope.
   valuePointer rho_prev = std::make_unique< values >() ;
   valuePointer rho      = std::make_unique< values >() ;
   valuePointer rho_next = std::make_unique< values >() ;
   valuePointer x        = std::make_unique< values >() ;

//   double* rho_prev = new double[npnts]; // time step t-1
//   double* rho     = new double[npnts]; // time step t
//   double* rho_next = new double[npnts]; // time step t+1
//   double* x      = new double[npnts]; // x values

   // Initialize
   for (int i = 0; i < npnts; i++) {
      x[i] = p.x1 + ((i-1)*(p.x2-p.x1))/ngrid; 
      rho[i] = 0.0;
      rho_prev[i] = 0.0;
      rho_next[i] = 0.0;
   }

   // Excite
   for (int i = npnts/4 + 1; i < 3*npnts/4; i++) {
      rho[i] = 0.25 - fabs(double(i-npnts/2)/double(npnts));
      rho_prev[i] = rho[i];
   }

   // Output initial signal
   std::cout << "\n#t = " << 0 << "\n";
   for (int i = 1; i <= ngrid; i++) 
      std::cout << x[i] << " " << rho[i] << "\n";

   // Take timesteps
   for (int sc = 0; sc < nsteps; sc++) {

      // Set zero dirichlet boundary conditions
      rho[0] = 0.0;
      rho[ngrid+1] = 0.0;

      // Evolve
      for (int i = 1; i <= ngrid; i++) {
         double laplacian = pow(p.c/s.dx,2)*(rho[i+1] + rho[i-1] - 2*rho[i]);
         double friction = (rho[i] - rho_prev[i])/p.tau;
         rho_next[i] = 2*rho[i] - rho_prev[i] + dt*(laplacian*dt-friction);
      }

      // Rotate array pointers so t+1 becomes the new t etc.
      double* temp = rho_prev;
      rho_prev = rho;
      rho     = rho_next;
      rho_next = temp;  

      // Output density
      if ((sc+1)%nper == 0) {
         std::cout << "\n\n# t = " << sc*dt << "\n";
         for (int i = 1; i <= ngrid; i++) 
            std::cout << x[i] << " " << rho[i] << "\n";
      }
   }

   // Deallocate memory
//   delete[] rho_prev;
//   delete[] rho;
//   delete[] rho_next;
//   delete[] x;

   return 0;
}
