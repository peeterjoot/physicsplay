/**
   \file output.cc
 */
#include "ants_on_table.h"
#include "optticktock.h"
#include <iostream>
#include "netcdfopen.h"

class netcdfOutput
{
   NcFileOpener m_out ;
   bool         m_open ;

public:
   netcdfOutput( ) : m_out{}, m_open{}
   {
   }

   netcdfOutput( const std::string netcdfFileName ) : m_out{}, m_open{}
   {
      if ( "" == netcdfFileName )
      {
         return ;
      }

      m_out.open( netcdfFileName, netCDF::NcFile::replace ) ;
      m_open = true ;
   }

   void writeTimeStep( const ants_on_table & a )
   {
   }
} ;

void output( ants_on_table & a, const int num_time_intervals, const std::string netcdfFileName )
{
   TickTockOrNoOp timer ;
   float ioTime { 0.0 } ;

   netcdfOutput out( netcdfFileName ) ;

   for ( int i = 0 ; i < num_time_intervals ; i++ )
   {
      float totants = a.total_number_of_ants() ;

      timer.tick() ;

      std::cout << i << " " << totants << std::endl ;

      ioTime += timer.silent_tock() ;

      out.writeTimeStep( a ) ;

      a.timestep() ;
   }

   #if defined USE_TICK_TOCK
      std::cout << "io time: \t"      << ioTime << std::endl ;
   #endif
}
