//
// ringoutput.cc
//
// Module for output for 1d diffusion or 1d random walk on a ring
//

#include "ringoutput.h"
#include <iostream>
#include <vector>
#include <cmath>
#include <numeric>
#include <iomanip>
#include <rarrayio>
#include "sparkline.h"

// based on: http://stackoverflow.com/a/7616783/189270
struct stats
{
   double m_sum ;
   double m_mean ;
   double m_sq_sum ;
   double m_stdev ;

public:
   stats( const darray & v )
   {
      m_sum = std::accumulate( v.begin(), v.end(), 0.0 ) ;
      m_mean = m_sum / v.size() ;
      double mean = m_mean ; // for lambda capture

      std::vector<double> diff( v.size() ) ;

      std::transform( v.begin(), v.end(), diff.begin(), [mean](double x) { return x - mean; } ) ;

      m_sq_sum = std::inner_product( diff.begin(), diff.end(), diff.begin(), 0.0 ) ;
      m_stdev = std::sqrt( m_sq_sum / v.size() ) ;
   }
} ;

ringoutput::ringoutput( const std::string & datafilename, const int outputcols )
   : m_outputcols( outputcols )
   , m_wasteTime( 0.0 )
{
   // First, open the file
   m_file.open( datafilename ) ;

   // Some initial output to screen
   std::cout << "   Step     Time   Walltime(s)    Mean      Stdev   Profile\n" ;

   // Start measuring elapsed time
   m_startTimer = ticks::sample() ;
}

static void reportToScreenToo( const darray & P, const double time, const int step, const int outputcols, const double timeSoFar )
{
   stats st( P ) ;

   std::cout << std::fixed << std::setw(7) << step  << " "
             << std::fixed << std::setprecision(2) << std::setw(8) << time << "   "
             << std::fixed << std::setprecision(4) << std::setw(8) << timeSoFar << "   "
             << std::setprecision(4) << std::setw(8) << st.m_mean << "   "
             << std::setprecision(4) << std::setw(8) << st.m_stdev << "   "
             << sparkline(P, outputcols, true) << std::endl ;
}

void ringoutput::showline( const int       step,
                           const double    time,
                           const darray &  P )
{
   auto t1 = ticks::sample() ;
   double timeSoFar = durationToSeconds(t1 - m_startTimer) - m_wasteTime ;

   // First, write rarray to file
   m_file << time << '\n' << P << "\n\n" ;

   reportToScreenToo( P, time, step, m_outputcols, timeSoFar ) ;

//   auto t2 = ticks::sample() ;
//   m_wasteTime += durationToSeconds(t2 - t1) ;
}

walkring_output::walkring_output( const std::string & datafilename, const int outputcols, const int N )
   : ringoutput( datafilename, outputcols )
   , m_density( N )
//   , m_N( N )
{
}

void walkring_output::showline( int step, double time, const rarray<int,1> &w )
{
   auto t1 = ticks::sample() ;
   auto timeSoFar = durationToSeconds(t1 - m_startTimer) - m_wasteTime ;

   m_density.fill(0) ;
   const auto oneWalkerDensity = 1.0/ w.size() ;

   for ( auto pos : w )
   {
      m_density[pos] += oneWalkerDensity ;
   }

   // First, write the rarray to file
   m_file << time << '\n' << m_density << " \n\n" ;

   reportToScreenToo( m_density, time, step, m_outputcols, timeSoFar ) ;

// FIXME: wanted to omit the internal times, but had some compilation issues along the way.  Do this if later if I
// have time (here and in ringoutput::showline).
//   auto t2 = ticks::sample() ;
//   m_wasteTime += durationToSeconds(t2 - t1) ;
}
