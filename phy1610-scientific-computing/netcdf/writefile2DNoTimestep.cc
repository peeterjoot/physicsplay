#include <netcdf>
#include "integers.h"
#include "physicsplay_build_version.h"
#include "returncodes.h"

using namespace netCDF ;
using namespace netCDF::exceptions ;

constexpr int nx{6}, ny{12} ;

void setData( int dataOut[nx][ny], const int v )
{
   for ( auto i{0} ; i < nx ; i++ )
   {
      for ( auto j{0} ; j < ny ; j++ )
      {
         dataOut[i][j] = i * ny + j + v ;
      }
   }
}

/**
   Parse arguments and run the driver.
 */
int main( int argc, char ** argv )
try 
{
   int dataOut[nx][ny] ;

   // Create the netCDF file.
   NcFile dataFile( "first.netCDF.nc", NcFile::replace ) ;

   // Create the dimensions.
   auto xDim = dataFile.addDim( "x", nx ) ;
   auto yDim = dataFile.addDim( "y", ny ) ;

   std::vector < NcDim > dims { xDim, yDim } ;

   // Create the data variable.
   auto data = dataFile.addVar( "data", ncInt, dims ) ;

   // Put the data in the file.
   data.putVar( &dataOut ) ;

   // Add an attribute.
   dataFile.putAtt( "Version info:", PHYSICSPLAY_COMMIT_INFO ) ;

   return (int)RETURNCODES::SUCCESS ;
}
catch ( NcException & e )
{
   std::cout << "unknown error" << std::endl ;
   e.what() ;

   return (int)RETURNCODES::EXCEPTION ;
}
