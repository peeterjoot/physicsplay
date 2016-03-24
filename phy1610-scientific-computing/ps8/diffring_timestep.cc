// 
// diffring_timestep.cc
//
// Time step module for 1d diffusion on a ring
//

#include "diffring_timestep.h"
#include <cblas.h>
#include "banded.h"

void diffring_evolution::perform_time_step( darray & P )
{
   // make tmpvec hold the input (X) vector, so that P can be the output (Y) vector in the dgemv
   // call.
   // This temporary vector serves two purposes:
   // 1) I'm assuming the input and output vectors (X) and (Y) are not allowed to alias each other
   //    in the blas call below.
   // 2) don't allocate/deallocate a new vector of this sort each time.
   std::swap( m_tmpvec, P ) ;

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
                CblasNoTrans, m_n, m_n,
                1.0, &m_F[0][0], m_n,
                &m_tmpvec[0], 1, 1.0,
                &P[0], 1 ) ;
}

void diffring_evolution::fill_time_step_matrix( const double   D,
                                                const double   dt,
                                                const double   dx )
{
   auto alpha { D * dt/(dx * dx) } ;
   auto diag { 1 - 2 * alpha } ;

   initializeBandedMatrix( m_F, alpha, diag, alpha, BANDING_TYPE::CYCLIC ) ;
}

diffring_evolution::diffring_evolution( const int      N,
                                        const double   D,
                                        const double   dt,
                                        const double   dx ) 
   : m_n( N ),
     m_tmpvec( N ),
     m_F( N, N )
{
   fill_time_step_matrix( D, dt, dx ) ;
}
