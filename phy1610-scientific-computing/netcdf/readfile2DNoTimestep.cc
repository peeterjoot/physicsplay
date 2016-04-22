// netCDF.reading.cpp
#include <iostream>
#include <netcdf>
#include "physicsplay_build_version.h"

using namespace netCDF ;
using namespace netCDF::exceptions ;

void printMatrix( const size_t nx, const size_t ny, int **p )
{
   for ( size_t i{0} ; i < nx; i++ )
   {
      for ( size_t j{0} ; j < ny; j++ )
      {
         std::cout << p[i][j] << " " ;
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

      auto nx = xDim.getSize() ;
      auto ny = yDim.getSize() ;

      std::cout << "Our matrix is " << nx << " by " << ny << ", with time dimension: " << nt << std::endl ;

      int **p = new int *[nx] ;
      p[0] = new int[nx * ny] ;

      for ( size_t i{0} ; i < nx; i++ )
      {
         p[i] = &p[0][i * ny] ;
      }

      // Create the data variable.
      auto data = dataFile.getVar( "data" ) ;

      // Put the data in a variable and print it.
      for ( size_t t{0} ; t < nt ; t++ )
      {
         data.getVar( p[0] ) ;

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
