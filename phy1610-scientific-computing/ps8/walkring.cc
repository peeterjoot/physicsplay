// 
// walkring.cc
//
// 1d random walk on a ring
//
// Compile with make using provided Makefile 
//

#include <fstream>
#include <rarray>
#include "ringoutput.h"
#include "walkring_timestep.h"
#include "walkring_parameters.h"

// the main function drives the simulation
int main(int argc, char *argv[]) 
{
  // Simulation parameters
  double      L;  // ring length
  double      D;  // diffusion constant
  double      T;  // time
  double      dx; // spatial resolution
  double      dt; // temporal resolution (time step)
  int         Z;  // number of walkers
  std::string datafile; // filename for output
  double      time_between_output;

  // Read parameters from a file given on the command line. 
  // If no file was given, use "walkring.ini".
  std::string paramFilename = argc>1?argv[1]:"walkring.ini";
  read_walking_parameters(paramFilename, L, D, T, dx, dt, Z, datafile, time_between_output);

  // Compute derived parameters 
  const int numSteps = int(T/dt + 0.5);  // number of steps to take
  const int N = int(L/dx + 0.5);         // number of grid points
  const int outputEvery = int(time_between_output/dt + 0.5); // how many steps between output
  const double p = D*dt/pow(dx,2);       // probability to hop left or right
  const int outputcols = 48;             // number of columns for sparkline output
    
  // Allocate walker data
  rarray<int,1> w(Z);
  // Setup initial conditions for w (i.e. all walkers at position zero to start)
  w.fill(0);
  // Setup initial time
  double time = 0.0;

  walkring_evolution evolution ;

  // Open a file for data output
  walkring_output out( datafile, outputcols, N ) ;  

  // Initial output to screen
  out.showline(0, time, w );

  // Time evolution
  for (int step = 1; step <= numSteps; step++) {

    // Compute next time point
    evolution.perform_time_step(w, N, p);

    // Update time
    time += dt;

    // Periodically add data to the file
    if (step % outputEvery == 0 and step > 0)      
      out.showline( step, time, w );
  }
  
  // All done
  return 0;
}
