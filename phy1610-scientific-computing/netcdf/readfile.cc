// netCDF.reading.cpp
#include <iostream>
#include <netcdf>
#include "physicsplay_build_version.h"

using namespace netCDF ;
using namespace netCDF::exceptions ;

void printMatrix( const size_t nx, const size_t ny, int * p )
{
   for ( size_t i{0} ; i < nx; i++ )
   {
      for ( size_t j{0} ; j < ny; j++ )
      {
         std::cout << p[i * ny + j] << " " ;
      }

      std::cout << std::endl ;
   }
}

int main()
{
   try {
      // Specify the netCDF file.
      NcFile dataFile( "first.netCDF.nc", NcFile::read ) ;

      // Read the two dimensions.
      auto xDim = dataFile.getDim( "x" ) ;
      auto yDim = dataFile.getDim( "y" ) ;
      auto tDim = dataFile.getDim( "t" ) ;

      size_t nx = xDim.getSize() ;
      size_t ny = yDim.getSize() ;
      size_t nt = tDim.getSize() ;

      std::cout << "Our matrix is " << nx << " by " << ny << ", with time dimension: " << nt << std::endl ;

      int p[nx * ny] ;

      // Create the data variable.
      auto data = dataFile.getVar( "data" ) ;

      std::vector<size_t> startp { 0, 0, 0 } ;
      // read one entry from the unlimited (timestep) dimension.
      std::vector<size_t> countp { 1, nx, ny } ;
      std::vector<ptrdiff_t> stridep { 1, 1, 1 } ;
      // in memory stride.  each data[t][x][y] -> data[t][ny * x + y]
      auto stridey{ (ptrdiff_t)ny } ;
      std::vector<ptrdiff_t> imapp { 1, stridey , 1 } ;

      // Put the data in a variable and print it.
      for ( size_t t{0} ; t < nt ; t++ )
      {
         startp[0] = t ;

         data.getVar( startp, countp, stridep, imapp, p ) ;

         printMatrix( nx, ny, p ) ;
      }
   }
   catch ( NcException & e )
   {
      std::cout << "unknown error" << std::endl ;
      e.what() ;
   }

   return 0 ;
}
