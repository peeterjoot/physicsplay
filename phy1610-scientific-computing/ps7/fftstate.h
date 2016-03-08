/** \file fftstate.h
 */
#if !defined phy1610_fftstate_h_included
#define phy1610_fftstate_h_included

#include <fftw3.h>
#include "carray.h"

/**
   A class to create, execute, and destroy a fft plan on rarray<complex,1> arrays of the same size,
   and a method to execute an in place FFT.
 */
class fftstate
{
   fftw_plan   m_plan ; ///< Cached plan for the FFT operation.
   size_t      m_sz ;   ///< save the initial array size and throw error if a different size is used.

public:
   /**
      Create an fftw3 plan for the supplied input array.

      \param s [in]
         Supply signal for the FFT plan creation.  All subsequent FFT executions with this object
         must use the same sized array (and according to the FFTW docs, must also have the same alignment.)
    */
   fftstate( carray & s ) ;

   /**
      In place fft, overriding the array location initially passed to the plan create.

      \param s [in,out]
         FFT input and output array.
    */
   void execute( carray & s ) ;

   /** destroy the fftw3 plan */
   ~fftstate() ;
} ;

#endif
