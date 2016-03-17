// 
// diffring_timestep.h
//
// Time step module for 1d diffusion on a ring
//

#ifndef DIFFRINGTIMESTEPH
#define DIFFRINGTIMESTEPH

#include <rarray>

// perform a single time step for the density field
// F: matrix that describes the time evolution
// P: the density
void perform_time_step(const rarray<double,2>& F, rarray<double,1>& P);

// fill the matrix needed in perform_time_step
// F: matrix that describes the time evolution
// D: the diffusion constant
// dt: the time step to be used
// dx: the spatial resolution
void fill_time_step_matrix(rarray<double,2>& F, double D, double dt, double dx);


#endif
