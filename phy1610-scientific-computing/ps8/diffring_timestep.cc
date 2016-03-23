// 
// diffring_timestep.cc
//
// Time step module for 1d diffusion on a ring
//

#include "diffring_timestep.h"
#include <cblas.h>
#include "banded.h"
#include "darray.h"

static darray tmpvec ;

// perform a single time step for the density field
// F: matrix that describes the time evolution
// P: the density
void perform_time_step(const rarray<double,2>& F, rarray<double,1>& P)
{
   auto n { getSquareMatrixDimensions( F ) } ;

   // make tmpvec hold the input (X) vector, so that P can be the output (Y) vector in the dgemv
   // call:
   std::swap( tmpvec, P ) ;

   // Slide 11, lecture 13:
   //Level 2: dgemv (dbl matrix*vec): double GEneral Matrix Vector.
   //
   // http://www.netlib.org/lapack/explore-html/d6/da2/cblas__dgemv_8c_source.html
   //void cblas_dgemv(const CBLAS_LAYOUT layout,
   //                 const CBLAS_TRANSPOSE TransA, const int M, const int N,
   //                 const double alpha, const double  *A, const int lda,
   //                 const double  *X, const int incX, const double beta,
   //                 double  *Y, const int incY)

   // UGG.  have to look at the fortran docs to see how to call this beastie!
   //
   // http://www.netlib.org/lapack/explore-html/d7/d15/group__double__blas__level2.html#gadd421a107a488d524859b4a64c1901a9
   cblas_dgemv( CblasRowMajor,
                CblasNoTrans, n, n,
                1.0, &F[0][0], n,
                &tmpvec[0], 1, 1.0,
                &P[0], 1 ) ;
}

// fill the matrix needed in perform_time_step
// F: matrix that describes the time evolution
// D: the diffusion constant
// dt: the time step to be used
// dx: the spatial resolution
void fill_time_step_matrix(rarray<double,2>& F, double D, double dt, double dx)
{
   // misses the initialization of the matrix F that performs the time evolution
   // (blas) matrix-vector multiplication in the perform time step. function. Note that most of the matrix
   // is similar to the one shown on page 17–19 on the slides of lecture 14. To implement the periodic
   // boundary conditions, the first and last row and the first and last column differ. In particular, if the
   // number of grid points is N, one should make sure that one satifies:
   // ...
   // This should introducing non-zero elements F[0][N-1] and F[N-1][0].

   // one time allocation of a temporary vector (assuming that cblas input and output
   // vectors are not allowed to alias each other).
   darray vec( F.extent(0) ) ;
   std::swap( tmpvec, vec ) ;

   auto alpha { D * dt/(dx * dx) } ;
   auto diag { 1 - 2 * alpha } ;

   initializeBandedMatrix( F, alpha, diag, alpha, BANDING_TYPE::CYCLIC ) ;
}
