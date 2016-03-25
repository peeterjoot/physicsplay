// 
// diffring.cc
//
// 1d diffusion on a ring
//
// Compile with make using provided Makefile 
//

#include <fstream>
#include <rarray>
#include "ringoutput.h"
#include "diffring_timestep.h"
#include "diffring_parameters.h"

// the main function drives the simulation
int main(int argc, char *argv[]) 
{
  // Simulation parameters
  double      L;  // ring length
  double      D;  // diffusion constant
  double      T;  // time
  double      dx; // spatial resolution
  double      dt; // temporal resolution (time step)
  //int         Z;  // number of walkers
  std::string datafile; // filename for output
  double      time_between_output;

  // Read parameters from a file given on the command line. 
  // If no file was given, use "diffring.ini".
  std::string paramFilename = argc>1?argv[1]:"diffring.ini";
  read_diffusion_parameters(paramFilename, L, D, T, dx, dt, datafile, time_between_output);

  // Compute derived parameters 
  const int numSteps = int(T/dt + 0.5);  // number of steps to take
  const int N = int(L/dx + 0.5);         // number of grid points
  const int outputEvery = int(time_between_output/dt + 0.5); // how many steps between output
  const int outputcols = 48;             // number of columns for sparkline output
  
  // Allocate density data 
  rarray<double,1> P(N);
  // Setup initial conditions for P
  P.fill(0.0);
  P[0] = 1.0;
  // Time evolution matrix
  diffring_evolution F(N, D, dt, dx);
  // Setup initial time
  double time = 0.0;    

  // Open a file for data output
  diffring_output out( datafile, outputcols ) ;  

  // Initial output
  out.showline( 0, time, P ) ;

  // Time evolution
  for (int step = 1; step <= numSteps; step++) {

    // Compute next time point
    F.perform_time_step(P);

    // Update time
    time += dt;

    // Periodically add data to the file
    if (step % outputEvery == 0 and step > 0) 
        out.showline( step, time, P );
  }
  
  // All done
  return 0;
}
