/** \file ratData.h
 */
#if !defined phy1610_ratData_h_included
#define phy1610_ratData_h_included

#include "darray.h"
#include "carray.h"

/**
   Storage for either the time domain:

   - (real) time mesh for the signal measurements.  For the FFT these are assumed to be equidistant.
   - signal values at each of the mesh points.

   or, frequency domain:

   - (real) power spectrum
   - FFT of the original time domain signal.

   The storage is recycled in this data structure since we don't need the original mesh nor time domain signal
   once we are ready to compute the FFT.
 */
struct ratData
{
   darray   m_timesOrPower ;
   carray   m_signalOrFFT ;

   /**
      Read a .rat file and populate the mesh and signal arrays.
    */
   void open( const std::string & ratPath,
              const std::string & filename ) ;

   /**
      Write the time domain mesh and the corresponding (complex) signal to a .csv file.
    */
   void writeToCsv( const std::string & outFileName ) const ;

   /**
      Write the power spectrum to a file for plotting.
    */
   void writePowerSpectrumToFile( const std::string & outFileName ) const ;

   /**
      overwrite m_timesOrPower with the power spectrum of m_signalOrFFT.
    */
   void calculatePowerSpectrum() ;
} ;

#endif
