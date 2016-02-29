#include <netcdf>
#include <getopt.h>
#include "integers.h"

using namespace netCDF ;
using namespace netCDF::exceptions;

/**
   return codes for this exe.
 */
enum class RETURNCODES : int
{
   SUCCESS,      ///< exit code for successful exectution
   HELP,         ///< exit code when -help (or bad option is supplied)
   PARSE_ERROR,  ///< exit code if there's a parse error */

   LAST
} ;

/** print the usage string for the program for --help (or unrecognized options)
 */
void showHelpAndExit()
{
   static_assert( (int)RETURNCODES::LAST <= 256, "exit code doesn't fit in waitpid waitstatus byte." ) ;

   std::cerr
      << "usage: example\n"
         "\t[--nrec]"
         "\t[--help]"
      << std::endl ;

   std::exit( (int)RETURNCODES::HELP ) ;
}

constexpr int nx = 6, ny = 12 ;

void setData( int dataOut[nx][ny], const int v )
{
   for ( int i = 0 ; i < nx; i++ )
   {
      for ( int j = 0 ; j < ny; j++ )
      {
         dataOut[i][j] = i * ny + j + v ;
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
      int dataOut[nx][ny] ;

      // Create the netCDF file.
      NcFile dataFile( "first.netCDF.nc", NcFile::replace ) ;

#define WITH_TIMESTEPS
      // Create the dimensions.
#if defined WITH_TIMESTEPS
      NcDim tDim = dataFile.addDim( "t" ) ;
#endif
      NcDim xDim = dataFile.addDim( "x", nx ) ;
      NcDim yDim = dataFile.addDim( "y", ny ) ;

      std::vector < NcDim > dims ;
#if defined WITH_TIMESTEPS
      dims.push_back( tDim ) ;
#endif
      dims.push_back( xDim ) ;
      dims.push_back( yDim ) ;

      // Create the data variable.
      NcVar data = dataFile.addVar( "data", ncInt, dims ) ;

      // Put the data in the file.
#if defined WITH_TIMESTEPS
      std::vector<size_t> startp ;
      std::vector<size_t> countp ;

      startp.push_back(0);
      startp.push_back(0);
      startp.push_back(0);

      countp.push_back(1);
      countp.push_back(nx);
      countp.push_back(ny);

      for ( Uint i = 0 ; i < nrec ; i++ )
      {
         setData( dataOut, i ) ;

         data.putVar( startp, countp, dataOut );
      }
#else
      data.putVar( &dataOut ) ;
#endif

      // Add an attribute.
      dataFile.putAtt( "Creation date:", "Feb 28, 2016" ) ;
   }
   catch (NcException& e)
   {
      std::cout << "unknown error" << std::endl;
      e.what() ;
   }

   return (int)RETURNCODES::SUCCESS ;
}
