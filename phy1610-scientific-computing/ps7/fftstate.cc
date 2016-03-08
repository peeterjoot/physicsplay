/**
   \file fftstate.cc

   Methods for fftw3 in place FFT operation: plan creation and execute.
 */
#include "fftstate.h"
#include "myexceptions.h"
#include <regex>
#include <iostream>

fftstate::fftstate( ratData & d )
   : m_plan{},
     m_sz{ (size_t)d.m_signalOrFFT.size() }
{
   // The fftw docs say that the plan should always be created before the signal 
   // is initialized, but that currently the arrays are not modified if FFTW_ESTIMATE
   // is used.  If that changed we'd have to re-initialize the data after creating the plan.
   // The rarrayio mechanism is the way we have to read the size, so we are forced to get the
   // size (and all the data) before creating the plan, so we are forced to do things opposite
   // to the suggested fftw3 order.  If we wanted to use FFTW_MEASURE, we'd have to re-read the
   // data after creating the plan.
   m_plan = fftw_plan_dft_1d( m_sz,
                              (fftw_complex*)&d.m_signalOrFFT[0],
                              (fftw_complex*)&d.m_signalOrFFT[0],
                              FFTW_FORWARD,
                              FFTW_ESTIMATE ) ;

   if ( !m_plan )
   {
       BOOST_THROW_EXCEPTION(
            plan_create_error()
               << asize_info( m_sz )
            ) ;
   }
}

void fftstate::execute( ratData & d )
{
   size_t newsize{ (size_t)d.m_signalOrFFT.size() } ;

   if ( m_sz != newsize )
   {
      BOOST_THROW_EXCEPTION(
           array_size_error()
              << asize_info( m_sz )
              << asize_info( newsize )
           ) ;
   }

   fftw_execute_dft( m_plan,
                     (fftw_complex*)&d.m_signalOrFFT[0],
                     (fftw_complex*)&d.m_signalOrFFT[0] ) ;
}
