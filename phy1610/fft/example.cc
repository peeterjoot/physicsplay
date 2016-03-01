/**
 \file example.cc
 */
#include <fftw3.h>
#include <cmath>
#include <iostream>
#include <getopt.h>
#include <fstream>
#include "integers.h"
#include "returncodes.h"

/** print the usage string for the program for --help (or unrecognized options)
 */
void showHelpAndExit()
{
   std::cerr
      << "usage: example\n"
         "\t[--infile]"
         "\t[--outfile]"
         "\t[--help]"
      << std::endl ;

   std::exit( (int)RETURNCODES::HELP ) ;
}

/**
   Parse arguments and run the driver.
 */
int main( int argc, char ** argv )
{
   int c{0} ;
   int line{0} ;

   std::string infile{} ;
   std::string outfile{} ;

   constexpr struct option long_options[]{
     { "help",           0, NULL, 'h' },
     { "infile",         1, NULL, 'i' },
     { "outfile",        1, NULL, 'o' },
     { NULL,             0, NULL, 0   }
   } ;

   try {
      while ( -1 != ( c = getopt_long( argc, argv, "hi:o:", long_options, NULL ) ) )
      {
         switch ( c )
         {
            case 'i' :
            {
               line = __LINE__ ;
               infile = std::string( optarg ) ;

               break ;
            }
            case 'o' :
            {
               line = __LINE__ ;
               outfile = std::string( optarg ) ;

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

   std::ofstream outfh( outfile.c_str() ) ;
   std::ofstream infh( infile.c_str() ) ;

   constexpr size_t N{ 1024 } ;
   constexpr double periods{ 5 } ;
   constexpr double delta{ 2 * M_PI * periods / N } ;
   constexpr double shift{ M_PI * periods } ;
   fftw_complex *in, *out ;
   fftw_plan p ;

   in = fftw_alloc_complex( N ) ;
   out = fftw_alloc_complex( N ) ;

   // [0,2 pi]
   double x { -shift } ;
   for ( Uint i = 0 ; i < N ; i++ )
   {
      auto & c = in[ i ] ;

      if ( 0.0 == x )
      {
         c[0] = 1.0 ;
         c[1] = 0.0 ;
      }
      else
      {
         c[0] = std::sin( x ) / x ;
         c[1] = 0.0 ;
      }

      x += delta ;
   }

   p = fftw_plan_dft_1d( N, in, out, FFTW_FORWARD, FFTW_ESTIMATE ) ;

   fftw_execute( p ) ;

   fftw_destroy_plan( p ) ;
   fftw_free( in ) ;

   x = -shift ;
   for ( Uint i = 0 ; i < N ; i++ )
   {
      infh << x << ", " << in[i][0] << "\n" ;

      outfh << x << ", " << out[i][0] << ", " << out[i][1] << "\n" ;

      x += delta ;
   }

   fftw_free( out ) ;

   return (int)RETURNCODES::SUCCESS ;
}
