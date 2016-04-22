//
// diffring_parameters.h
//
// Module for reading parameters for 1d diffusion on a ring
//

#ifndef DIFFRINGPARAMETERSH
#define DIFFRINGPARAMETERSH

#include <string>

// The 'read_diffusion_parameters' function reads in the file
// inifilename and stores the parameters in that file in the variables
// L, D, T, dx, dt, datafile and time_between_output.
void read_diffusion_parameters(const std::string &inifilename,
                               double&      L,        // ring length
                               double&      D,        // diffusion constant
                               double&      T,        // total time
                               double&      dx,       // spatial resolution
                               double&      dt,       // temporal resolution (time step)
                               std::string& datafile, // Name of the output file
                               double&      time_between_output); // controls how frequently the program writes out

#endif
