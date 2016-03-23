/** \file banded.h
 */
#if !defined phy1610_banded_h_included
#define phy1610_banded_h_included

#include "rarray"

/** rarray object assumed to be a two-by-two matrix */
using darray2 = rarray<double, 2> ;

/** parameters for initializeBandedMatrix::how */
enum class BANDING_TYPE 
{
   TRIDIAGONAL,
   CYCLIC
} ;

/** 
   Construct a tridiagonal matrix, overwriting any previous contents.

   \param m [in,out]
      The square matrix to write into.

   \param subdiagonal [in]
      The value to write onto all entries of the subdiagonal.

   \param diagonal [in]
      The value to write onto all entries of the diagonal.

   \param superdiagonal [in]
      The value to write onto all entries of the superdiagonal.

   \param how [in]
      One of INITIALIZE_BANDED or INITIALIZE_BANDED_CYCLIC.

      If INITIALIZE_BANDED_CYCLIC is specified, the subdiagonal value is put into the (1,N) location,
      and the superdiagonal value into the (N,1) location.
 */
void initializeBandedMatrix( darray2 &          m,
                             const double        subdiagonal,
                             const double        diagonal,
                             const double        superdiagonal,
                             const BANDING_TYPE  how ) ;

#endif
