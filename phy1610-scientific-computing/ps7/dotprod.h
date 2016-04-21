/** \file dotprod.h

   Defines a cblas dot product function and a correlator class to test data against a reference signal.
 */
#if !defined phy1610_dotprod_h_included
#define phy1610_dotprod_h_included

#include <cblas.h>
#include "darray.h"

/**
   Compute the dot product of two real (double typed) vectors using cblas_ddot.
 */
double dotprod( const darray & f, const darray & g ) ;

/**
   Compute the correlation for two power spectrums.
 */
class correlator
{
   const darray &    m_pred ;  ///< real reference signal data.
   double            m_dotff ; ///< dotprod( m_pred, m_pred ).  This is precomputed since it is required for all the comparisons.

public:

   /**
      Initialize the correlator object, caching the dot product of the reference signal.

      \param referenceSignal [in]
         Real (such as the positive frequency domain power spectrum) reference signal to use for subsequent correlation calculations.
     */
   correlator( const darray & referenceSignal ) ;

   /**
      Compute the correlation of det with respect to the saved power spectrum signal m_pred.

      \param det [in]
         A signal to check against the reference signal (i.e. the real positive power spectrum for a detected signal in the frequency domain.)

      \retval
         The coorelation of the two signals.
    */
   double operator()( const darray & det ) const ;
} ;

#endif
