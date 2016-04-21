// netCDF.reading.cpp
#include <iostream>
#include <netcdf>
#include <algorithm>
#include <getopt.h>
#include "returncodes.h"

/** print the usage string for the program for --help (or unrecognized options)
 */
void showHelpAndExit()
{
   std::cerr << "usage: readants --netcdf=filename|-f filename]\n"
                "\t[--help]" << std::endl ;

   std::exit( (int)RETURNCODES::HELP ) ;
}

using namespace netCDF ;
using namespace exceptions ;

/**
   Parse arguments and run the driver.
 */
int main( int argc, char ** argv )
{
   int c{0} ;
   int line{0} ;
   std::string netcdffilename{} ;

   constexpr struct option long_options[]{
     { "help",           0, NULL, 'h' },
     { "netcdf",         1, NULL, 'f' },
     { NULL,             0, NULL, 0   }
   } ;

   try {
      while ( -1 != ( c = getopt_long( argc, argv, "hf:", long_options, NULL ) ) )
      {
         switch ( c )
         {
            case 'f' :
            {
               line = __LINE__ ;
               netcdffilename = optarg ;

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
   catch ( ... )
   {
      std::cerr
         << __FILE__
         << ":"
         << line << ": uncaught exception (parse error)\n"
         << "option: -" << (char)c << '\n'
         << "argument: " << optarg << '\n'
         << std::endl ;

      std::exit( (int)RETURNCODES::PARSE_ERROR ) ;
   }

   if ( netcdffilename == "" )
   {
      showHelpAndExit() ;
   }

   try {
      // Specify the netCDF file.
      NcFile dataFile( netcdffilename, NcFile::read ) ;

      // Read the two dimensions.
      auto xDim = dataFile.getDim( "x" ) ;
      auto yDim = dataFile.getDim( "y" ) ;
      auto tDim = dataFile.getDim( "t" ) ;

      auto nx = xDim.getSize() ;
      auto ny = yDim.getSize() ;
      auto nt = tDim.getSize() ;

      std::cout << "Our matrix is " << nx << " by " << ny << ", with time dimension: " << nt << std::endl ;

      std::vector<float> p( nx * ny ) ;

      // Create the data variable.
      auto grid = dataFile.getVar( "grid" ) ;
      auto total = dataFile.getVar( "total" ) ;

      std::vector<size_t> startp { 0, 0, 0 } ;
      // read one entry from the unlimited (timestep) dimension.
      std::vector<size_t> countp { 1, nx, ny } ;
      std::vector<ptrdiff_t> stridep { 1, 1, 1 } ;
      // in memory stride.  each data[t][x][y] -> data[t][ny * x + y]
      auto stridey{ (ptrdiff_t)ny } ;
      std::vector<ptrdiff_t> imapp { 1, stridey , 1 } ;

      float err{} ;

      // Put the data in a variable and print it.
      for ( size_t t{0} ; t < nt ; t++ )
      {
         startp[0] = t ;

         grid.getVar( startp, countp, stridep, imapp, &p[0] ) ;

         std::vector<size_t> index{ t } ;

         float totants{} ;

         total.getVar( index, &totants ) ;

         float totgridants = std::accumulate( p.begin(), p.end(), 0.0f ) ;

         err += std::abs( totants - totgridants ) ;

         //std::cout << "total: var: " << totants << std::endl ;
         std::cout << "total: sum: " << totgridants << std::endl ;
      }

      std::cout << "err: " << err << std::endl ;
   }
   catch ( NcException & e )
   {
      std::cout << "unknown error" << std::endl ;

      e.what() ;
   }

   return (int)RETURNCODES::SUCCESS ;
}
