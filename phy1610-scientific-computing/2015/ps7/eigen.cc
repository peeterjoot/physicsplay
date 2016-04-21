// http://stackoverflow.com/questions/21701496/lapacke-eigen-solution-is-inaccurate-how-to-improve-it
/**
 * eigen.cpp
 * 
 * Given that you put version 3.5.0 into /opt/lapack/ compile this with: 
 * g++ eigen.cpp -I"/opt/lapack/lapack-3.5.0/lapacke/include" \
       -L"/opt/lapack/lapack-3.5.0" -llapacke -llapack -lblas -lcblas
 * The order of included libraries is important!
 */

#include <iostream>
#include <string>
#include <sstream>
// cstdlib needs including before clapack!
#include <cstdlib>
#include <cblas.h>
#include <lapacke.h>

using namespace std ;

/** Column major style! */
string
matrix2string( int m, int n, const double *A)
{
   ostringstream oss ;

   for ( int j = 0; j < m; j++)
   {
      for ( int k = 0; k < n; k++)
      {
         oss << A[j + k * m] << "\t" ;
      }

      oss << endl ;
   }

   return oss.str() ;
}

int main(int argc, char **argv)
{
   //> Preliminaries. -------------------------------------------------
   // Column Major Matrices for setting up the problem.
   double D_orig[9] = {
      2, 0, 0,
      0, -3, 0,
      0, 0, 0
   } ;
   double EV_orig[9] = {
      3. / 5., 4. / 5., 0,
      -4. / 5., 3. / 5., 0,
      0, 0, 1
   } ;
   double A[9] = { 0, 0, 0, 0, 0, 0, 0, 0, 0 } ;
   double dummy[9] = { 0, 0, 0, 0, 0, 0, 0, 0, 0 } ;

   // A = EV D EV'
   // dummy := D EV'
   // A := EV dummy
   cblas_dgemm( CblasColMajor, CblasNoTrans, CblasTrans, 3, 3, 3, 1,
                &D_orig[0], 3, &EV_orig[0], 3, 0, &dummy[0], 3) ;
   cblas_dgemm( CblasColMajor, CblasNoTrans, CblasNoTrans, 3, 3, 3, 1,
                &EV_orig[0], 3, &dummy[0], 3, 0, &A[0], 3) ;

   cout << "Set up the problem building A = EV D EV'" << endl 
        << "EV = [" << endl 
        << matrix2string( 3, 3, &EV_orig[0]).  c_str( ) << "];" << endl
        << "D = [" << endl << matrix2string( 3, 3, &D_orig[0]).c_str( ) << "];" << endl
        << "A = [" << endl << matrix2string( 3, 3, &A[0]).c_str( ) << "];" << endl
 ;

   //< ----------------------------------------------------------------
   //> Actual eigen value problem. ------------------------------------
   char jobz = 'V';         // We want both vectors and values.
   char uplo = 'L';         // 'L' means lower triangular input A as opposed to 'U'.
   int N = 3;             // Matrix dimension, or as they call it, 'order'.
   // As stated by example ATriL is unnecessary. Just replace all of its
   // occurences with plain A and all is well.
   //   double ATriL[9] = { A[0], A[1], A[2], A[4], A[5], A[8], 0, 0, 0 }; // Lower Triangle of symmetric A.
   #define ATriL A

   // Note that it is larger than necessary. It will contain the eigenvectors at the end.
   int lda = 3 ;
   //double w[3] = { 0, 0, 0 }; // Container for the eigenvalues.
   int lwork = 15;         // Size of the worker array. Set to (NB+2)*N where NB here is the largest blocksize.
   // Note, however, that the definition of NB is more complex.
   // Compare http://ftp.mcs.anl.gov/pub/MINPACK-2/lapack/ilaenv.f
   double work[lwork] ;
   int info = 0 ;

   // "double symmetric eigenvalue problem" I presume.
   // lapack_int LAPACKE_dsyev( int matrix_order, char jobz, char uplo, lapack_int n,
   //                                        double* a, lapack_int lda, double* w ) ;
   info =
      LAPACKE_dsyev( LAPACK_COL_MAJOR, jobz, uplo, N, &ATriL[0], lda, &work[0] ) ;

   // Note that the function takes no parameters lwork and w and that the
   // eigenvalues appear to be written into work.
   cout << "Ran dsyev(..) -- presumably 'double symmetric eigenvalue'." << endl
        << "Lambda: " << work[0] << ", " << work[1] << ", " << work[2] << endl
        << "EV = [" << endl << matrix2string( 3, 3, &ATriL[0]) << "];" << endl 
        << "Info: " << info << endl ;

   //< ----------------------------------------------------------------
   return EXIT_SUCCESS ;
}
