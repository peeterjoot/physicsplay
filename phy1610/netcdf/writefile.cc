#include <netcdf>
#include <getopt.h>
#include "integers.h"
#include "physicsplay_build_version.h"
#include "returncodes.h"

using namespace netCDF ;
using namespace netCDF::exceptions ;

/** print the usage string for the program for --help (or unrecognized options)
 */
void showHelpAndExit()
{
   std::cerr
      << "usage: example\n"
         "\t[--nrec]"
         "\t[--help]"
      << std::endl ;

   std::exit( (int)RETURNCODES::HELP ) ;
}

constexpr int nx = 6, ny = 12 ;

void setData( int * dataOut, const int v )
{
   for ( int i = 0 ; i < nx; i++ )
   {
      for ( int j = 0 ; j < ny; j++ )
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
   int c{0} ;
   int line{0} ;
   Uint nrec{ 1 } ;

   constexpr struct option long_options[]{
     { "help",           0, NULL, 'h' },
     { "nrec",           1, NULL, 'n' },
     { NULL,             0, NULL, 0   }
   } ;

   try {
      while ( -1 != ( c = getopt_long( argc, argv, "hn:", long_options, NULL ) ) )
      {
         switch ( c )
         {
            case 'n' :
            {
               line = __LINE__ ;
               nrec = strToUint( optarg ) ;

               break ;
            }
            case 'h' :
            default:
            {
               showHelpAndExit() ;
            }
         }
      }
   }
   catch (...)
   {
      std::cerr
         << __FILE__
         << ":"
         << line << ": uncaught exception (parse error)\n"
         << "option: -" << (char)c << "\n"
         << "argument: " << optarg << "\n"
         << std::endl ;

      std::exit( (int)RETURNCODES::PARSE_ERROR ) ;
   }

   try {
      int dataOut[nx * ny] ;

      // Create the netCDF file.
      NcFile dataFile( "first.netCDF.nc", NcFile::replace ) ;

      // Create the dimensions.
      NcDim tDim = dataFile.addDim( "t" ) ;
      NcDim xDim = dataFile.addDim( "x", nx ) ;
      NcDim yDim = dataFile.addDim( "y", ny ) ;

      std::vector < NcDim > dims { tDim, xDim, yDim } ;

      // Create the data variable.
      NcVar data = dataFile.addVar( "data", ncInt, dims ) ;

      // Put the data in the file.
      std::vector<size_t> startp { 0, 0, 0 } ;
      constexpr size_t nt{ 1 } ; // write one entry to the unlimited dimension.
      std::vector<size_t> countp { nt, nx, ny } ;
      std::vector<ptrdiff_t> stridep { 1, 1, 1 } ;
      // in memory stride.  each data[t][x][y] -> data[t][ny * x + y]
      constexpr size_t stridey{ ny } ;
      std::vector<ptrdiff_t> imapp { 1, stridey , 1 } ;

      for ( Uint i = 0 ; i < nrec ; i++ )
      {
         startp[0] = i ; // This is controlling the timestep location for the write

         setData( dataOut, i ) ;

         // https://www.unidata.ucar.edu/software/netcdf/docs/cxx4/classnetCDF_1_1NcVar.html#a763b0a2d6665ac22ab1be21b8b39c102
         data.putVar( startp, countp, stridep, imapp, dataOut ) ;
      }

      // Add an attribute.
      dataFile.putAtt( "Version info:", PHYSICSPLAY_COMMIT_INFO ) ;
   }
   catch (NcException& e)
   {
      std::cout << "unknown error" << std::endl ;
      e.what() ;
   }

   return (int)RETURNCODES::SUCCESS ;
}
