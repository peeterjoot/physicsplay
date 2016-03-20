// 
// diffring_timestep.cc
//
// Time step module for 1d diffusion on a ring
//

#include "diffring_timestep.h"
#include <cblas.h>

// perform a single time step for the density field
// F: matrix that describes the time evolution
// P: the density
void perform_time_step(const rarray<double,2>& F, rarray<double,1>& P)
{
   // FIXME: PART 2:
   // misses the appropriate (blas) matrix-vector multiplication in the perform time step function.
}

// fill the matrix needed in perform_time_step
// F: matrix that describes the time evolution
// D: the diffusion constant
// dt: the time step to be used
// dx: the spatial resolution
void fill_time_step_matrix(rarray<double,2>& F, double D, double dt, double dx)
{
   // FIXME: PART 1.
   // misses the initialization of the matrix F that performs the time evolution
   // (blas) matrix-vector multiplication in the perform time step. function. Note that most of the matrix
   // is similar to the one shown on page 17–19 on the slides of lecture 14. To implement the periodic
   // boundary conditions, the first and last row and the first and last column differ. In particular, if the
   // number of grid points is N, one should make sure that one satifies:
   // ...
   // This should introducing non-zero elements F[0][N-1] and F[N-1][0].
}
