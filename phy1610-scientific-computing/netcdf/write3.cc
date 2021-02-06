#include <netcdf>
#include "integers.h"
#include "physicsplay_build_version.h"
#include "returncodes.h"
#include "parseoptions.h"
#include <assert.h>

using namespace netCDF ;
using namespace netCDF::exceptions ;

constexpr int nx{6}, ny{12}, nz{3} ;
using varType = double;

void setData( varType * dataOut, const int v ) {
   for ( auto i{0} ; i < nx; i++ ) {
      for ( auto j{0} ; j < ny; j++ ) {
         for ( auto k{0} ; k < nz; k++ ) {
            // data[x][y] -> data[ny * x + y]
            // data[x][y][z] -> data[nz*ny * x + nz * y + z]
            auto p = k + nz * j + nz * ny * i;
            assert( p < nx*ny*nz );

            dataOut[ p ] = i + j + k + v;
         }
      }
   }
}

/**
   Parse arguments and run the driver.
 */
int main( int argc, char ** argv ) {
   parseOptions opt( argc, argv ) ;

   try {
      varType dataOut[nx * ny * nz]{};

      // Create the netCDF file.
      NcFile dataFile( "first.netCDF.nc", NcFile::replace ) ;

      // Create the dimensions.
      auto xDim = dataFile.addDim( "x", nx ) ;
      auto yDim = dataFile.addDim( "y", ny ) ;
      auto zDim = dataFile.addDim( "z", nz ) ;

      std::vector < NcDim > dims { xDim, yDim, zDim } ;

      // Create the data variable.
      auto data = dataFile.addVar( "data", ncDouble, dims ) ;

      // Put the data in the file.
      std::vector<size_t> startp { 0, 0, 0 } ;
      std::vector<size_t> countp { nx, ny, nz } ;
      std::vector<ptrdiff_t> stridep { 1, 1, 1 } ;
      // in memory stride.  each data[x][y] -> data[ny * x + y]
      std::vector<ptrdiff_t> imapp { 1, ny , nz } ;

      for ( Uint i{0} ; i < opt.nrec() ; i++ )
      {
         startp[0] = i ;

         setData( dataOut, i ) ;

         data.putVar( startp, countp, stridep, imapp, dataOut ) ;
      }

      // Add an attribute.
      dataFile.putAtt( "Version info:", PHYSICSPLAY_COMMIT_INFO ) ;
   }
   catch ( NcException & e )
   {
      std::cout << "caught: " << e.what() << "\n";
   }

   return (int)RETURNCODES::SUCCESS ;
}
