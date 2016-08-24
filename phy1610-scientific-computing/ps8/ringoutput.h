/** \file ringoutput.h

   Module for output for 1d diffusion or random walk on a ring
 */
#if !defined phy1610_ringoutput_h_included
#define phy1610_ringoutput_h_included

#include <fstream>
#include <rarray>
#include "ticks.h"
#include "darray.h"

/**
   A class to display a histogram of the density, and write the density at each grid point to a file.
  */
class ringoutput
{
protected:
   std::ofstream  m_file ;             ///< File handle for the .dat output.
   int            m_outputcols ;       ///< Width of the output graph.
   double         m_wasteTime ;
   ticks          m_startTimer ;

public:
   /**
      Setup output into a file of file name datafilename.

      A header will be written to screen as well.

      \param datafilename [in]
         Name of the file to open.

      \param Number of grid points [in]
         Specify this for a walkring
    */
   ringoutput( const std::string & datafilename, const int outputcols ) ;

   /**
      Output into a file of file name datafilename. There will be other
      output to screen as well, such as a little graph of the density.

      \param step [in]
         Number of the current time step.

      \param time [in]
         Current value of the time.

      \param P [in]
         Density array.
    */
   void showline( const int         step,
                  const double      time,
                  const darray   &  P ) ;
} ;

using diffring_output = ringoutput ;

class walkring_output : private ringoutput
{
private:
   darray   m_density ;    ///< An internally calculated density, calculated once per output line.  This is written to the .dat file instead of showline's w parameter.
//   int      m_N ;          ///< Number of grid points.

public:
   /**
      Setup output into a file of file name datafilename.

      A header will be written to screen as well.

      \param datafilename [in]
         Name of the file to open.

      \param N [in]
         Number of grid points.
    */
   walkring_output( const std::string & datafilename, const int outputcols, const int N ) ;

   /**
      This function calculates a density array from the walker positions, and outputs
      that and the histogram of that data.

      This allows us to produce more comparable .dat files than the original
      diffring_output.* and walkring_output.* modules originally produced (i.e. the .dat
      output is normalized to the diffring density format for output).

      \param step [in]
         Number of the current time step.

      \param time [in]
         Current value of the time.

      \param w [in]
         Position of the walkers.
    */
   void showline( const int                  step,
                  const double               time,
                  const rarray<int, 1> &     w ) ;
} ;

#endif
