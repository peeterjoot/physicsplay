/** \file fftstate.h
 */
#if !defined phy1610_fftstate_h_included
#define phy1610_fftstate_h_included

#include <fftw3.h>
#include "ratData.h"

/**
   A class to create, execute, and destroy a fft plan on rarray<complex,1> arrays of the same size.
 */
class fftstate
{
   fftw_plan   m_plan ;
   size_t      m_sz ;

public:
   /**
      Create an fftw3 plan for the ratData::m_signal sized array.
    */
   fftstate( ratData & d ) ;

   /** in place fft, overriding the array location initially passed to the plan create */
   void execute( ratData & d ) ;

   /** destroy the fftw3 plan */
   ~fftstate()
   {
      fftw_destroy_plan( m_plan ) ;
   }
} ;

#endif
