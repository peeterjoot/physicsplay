/**
   \file output.cc
 */
#include "ants_on_table.h"
#include "optticktock.h"
#include <iostream>
#include "netcdfopen.h"
#include <type_traits>
#include "physicsplay_build_version.h"

class netcdfOutput : public NcFileOpener
{
   bool                    m_open ;
   netCDF::NcVar           m_data ;
   std::vector<size_t>     m_startp ;
   std::vector<size_t>     m_countp ;
   std::vector<ptrdiff_t>  m_stridep ;
   std::vector<ptrdiff_t>  m_imapp ;

public:
   netcdfOutput( const std::string netcdfFileName, const size_t n ) :
      NcFileOpener{},
      m_open{},
      m_data{},
      m_startp { 0, 0, 0 },
      m_countp { 1, n, n },
      m_stridep { 1, 1, 1 },
      // in memory stride.  each data[t][x][y] -> data[t][n * x + y]
      m_imapp { 1, (ptrdiff_t)n , 1 }
   {
      if ( "" == netcdfFileName )
      {
         return ;
      }

      open( netcdfFileName, netCDF::NcFile::replace ) ;
      m_open = true ;

      // Create the dimensions.
      netCDF::NcDim tDim = h->addDim( "t" ) ;
      netCDF::NcDim xDim = h->addDim( "x", n ) ;
      netCDF::NcDim yDim = h->addDim( "y", n ) ;

      std::vector < netCDF::NcDim > dims { tDim, xDim, yDim } ;

      // Create the data variable.
      m_data = h->addVar( "data", netCDF::ncFloat, dims ) ;

      h->putAtt( "Version info:", PHYSICSPLAY_COMMIT_INFO ) ;

      // ncdump is showing zeros for the entries once less than 1.
      //h->putAtt( "data:C_format", "%.7g" ) ;
   }

   void writeTimeStep( const ants_on_table & a, const size_t timestep )
   {
      if ( !m_open || timestep > 0 )
      {
         return ;
      }

      m_startp[0] = timestep ; // This is controlling the timestep location for the write

      ants_on_table::ants_storage_type p = a.antsBackingArray() ;

#if defined MYRARRAY_USING_RARRAY
      m_data.putVar( m_startp, m_countp, m_stridep, p ) ;
#else
      m_data.putVar( m_startp, m_countp, m_stridep, m_imapp, p ) ;
#endif
   }
} ;

void output( ants_on_table & a, const int num_time_intervals, const std::string netcdfFileName )
{
   TickTockOrNoOp timer ;
   float ioTime { 0.0 } ;

   netcdfOutput out( netcdfFileName, a.table_grid_size() ) ;

   for ( int i = 0 ; i < num_time_intervals ; i++ )
   {
      float totants = a.total_number_of_ants() ;

      timer.tick() ;

      std::cout << i << " " << totants << std::endl ;

      ioTime += timer.silent_tock() ;

      out.writeTimeStep( a, i ) ;

      a.timestep() ;
   }

   #if defined USE_TICK_TOCK
      std::cout << "io time: \t"      << ioTime << std::endl ;
   #endif
}
