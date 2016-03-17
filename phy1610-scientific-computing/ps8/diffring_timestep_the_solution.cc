// 
// diffring_timestep.cc
//
// Time step module for 1d diffusion on a ring
//

#include "diffring_timestep.h"
#include <cblas.h>

// perform a single time step for the random walkers
void perform_time_step(const rarray<double,2>& F, rarray<double,1>& P)
{
    static rarray<double,1> Pold(P.size());
    // interchange P and Pold
    std::swap(P, Pold);
    // P = M * Pold
    cblas_dgemv(CblasRowMajor, CblasNoTrans,
                F.extent(0), F.extent(1), 1.0, F.data(), F.extent(1),
                Pold.data(), 1, 0.0, P.data(), 1);
}

// fill the matrix needed in perform_time_step
void fill_time_step_matrix(rarray<double,2>& F, double D, double dt, double dx)
{
  int nrows = F.extent(0);
  int ncols = F.extent(1);
  F.fill(0.0);
  double a = D*dt/pow(dx,2);  // off-diagonal value
  double d = 1 - 2*a;         // diagonal value
  for (int r=1; r<nrows; r++) {
      F[r-1][r] = a;      
      F[r][r]   = d;
      F[r][r-1] = a;
  }
  F[0][0] = d;
  F[0][ncols-1] = a;
  F[nrows-1][0] = a;
}
