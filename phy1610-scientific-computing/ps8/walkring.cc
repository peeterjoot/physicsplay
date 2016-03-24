// 
// walkring.cc
//
// 1d random walk on a ring
//
// Compile with make using provided Makefile 
//

#include <fstream>
#include <rarray>
#include "walkring_output.h"
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
  // Setup initial conditions for w
  w.fill(0);
   // Setup initial time
  double time = 0.0;

  // Open a file for data output
  std::ofstream file;
  walkring_evolution evolution ;
  output_init(file, datafile);  
  // Initial output to screen
  output(file, 0, time, N, w, outputcols);

  // Time evolution
  for (int step = 1; step <= numSteps; step++) {

    // Compute next time point
    evolution.perform_time_step(w, N, p);

    // Update time
    time += dt;

    // Periodically add data to the file
    if (step % outputEvery == 0 and step > 0)      
      output(file, step, time, N, w, outputcols);
  }
  
  // Close file
  output_finish(file);

  // All done
  return 0;
}

