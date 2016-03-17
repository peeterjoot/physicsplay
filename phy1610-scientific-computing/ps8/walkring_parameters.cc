// 
// walkring_parameters.cc
//
// Module for reading parameters for 1d random walk on a ring
//

#include "walkring_parameters.h"
#include "inifile.h"

void read_walking_parameters(const std::string &inifilename, 
			     double&      L,        // ring length
                             double&      D,        // diffusion constant
                             double&      T,        // total time
                             double&      dx,       // spatial resolution
                             double&      dt,       // temporal resolution (time step)
                             int&         Z,        // number of walkers
                             std::string& datafile, // Name of the output file
                             double&      time_between_output) // controls how frequently the program writes out
{
  // This function reads in the file inifilename and stores the
  // parameters in that file in the variables L, D, T, dx, dt, Z,
  // datafile and time_between_output.

    
  // Open inifile and parse (using Inifile class from inifile.h)
  Inifile parameter(inifilename);
      
  // Simulation parameters (defaults are given in case they are not in the file)
  L  = parameter.get<double>("L", 24.0);       // ring length
  D  = parameter.get<double>("D",  1.0);       // diffusion constant
  T  = parameter.get<double>("T", 30.0);       // time
  dx = parameter.get<double>("dx", 0.01);      // spatial resolution
  dt = parameter.get<double>("dt", 3.0e-5);    // temporal resolution (time step)
  Z  = parameter.get<int>("walkers", 20);      // number of walkers

  // Output parameters
  datafile = parameter.get<std::string>("data_file","walkring.dat");
  time_between_output = parameter.get<double>("time_between_output", 0.3);
}
  
