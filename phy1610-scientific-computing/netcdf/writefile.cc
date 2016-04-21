#include <netcdf>
#include "integers.h"
#include "physicsplay_build_version.h"
#include "returncodes.h"
#include "parseoptions.h"

using namespace netCDF ;
using namespace netCDF::exceptions ;

constexpr int nx{6}, ny{12} ;

void setData( int * dataOut, const int v )
{
   for ( auto i{0} ; i < nx; i++ )
   {
      for ( auto j{0} ; j < ny; j++ )
      {
         dataOut[i * ny + j] = i * ny + j + v ;
      }
   }
}

/**
   Parse arguments and run the driver.
 */
int main( int argc, char ** argv )
{
   parseOptions opt( argc, argv ) ;

   try {
      int dataOut[nx * ny] ;

      // Create the netCDF file.
      NcFile dataFile( "first.netCDF.nc", NcFile::replace ) ;

      // Create the dimensions.
      auto tDim = dataFile.addDim( "t" ) ;
      auto xDim = dataFile.addDim( "x", nx ) ;
      auto yDim = dataFile.addDim( "y", ny ) ;

      std::vector < NcDim > dims { tDim, xDim, yDim } ;

      // Create the data variable.
      auto data = dataFile.addVar( "data", ncInt, dims ) ;

      // Put the data in the file.
      std::vector<size_t> startp { 0, 0, 0 } ;
      constexpr size_t nt{ 1 } ; // write one entry to the unlimited dimension.
      std::vector<size_t> countp { nt, nx, ny } ;
      std::vector<ptrdiff_t> stridep { 1, 1, 1 } ;
      // in memory stride.  each data[t][x][y] -> data[t][ny * x + y]
      constexpr size_t stridey{ ny } ;
      std::vector<ptrdiff_t> imapp { 1, stridey , 1 } ;

      for ( Uint i{0} ; i < opt.nrec() ; i++ )
      {
         startp[0] = i ; // This is controlling the timestep location for the write

         setData( dataOut, i ) ;

         // https://www.unidata.ucar.edu/software/netcdf/docs/cxx4/classnetCDF_1_1NcVar.html#a763b0a2d6665ac22ab1be21b8b39c102
         data.putVar( startp, countp, stridep, imapp, dataOut ) ;
      }

      // Add an attribute.
      dataFile.putAtt( "Version info:", PHYSICSPLAY_COMMIT_INFO ) ;
   }
   catch ( NcException & e )
   {
      std::cout << "unknown error" << std::endl ;
      e.what() ;
   }

   return (int)RETURNCODES::SUCCESS ;
}
