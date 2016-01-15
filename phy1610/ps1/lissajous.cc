/**
   \file lissajous.cc

   The program is to generate a table of data. The table should have
   three columns, one column with x double precision values ranging
   from -5 to 5, a second column with values y=sin(2x), and a third
   column with values z=cos(3x). In particular, your program should:

      - Contain at least two functions (besides ”int main”), called ”f”
        and ”g”. The function ”f” should take x as an argument and
        return the value of sin(2x), while the function ”g” should that
        take x as an argument and return cos(3x).
      - The program should take 100 evenly spaced x-values from the
        interval [-5,5].
      - It should use the functions f and g to compute the values of
        those functions for those 100 x-values.
      - It should write out the x and y values in tabular form (i.e.
        three-column ascii text), either to a file called ”lissajous.txt”.

   Don’t try to add lines to the table, just use spaces and
   newlines to format the text.
*/
#include <cmath>
#include <cassert>
#include <iostream>
#include <cstring>
#include <cstdlib>
#include <getopt.h>

#include "integers.h"

#define SINE_MULTIPLIER 2
#define COSINE_MULTIPLIER 3
#define LOWER_INTERVAL_BOUND -5.0
#define UPPER_INTERVAL_BOUND 5.0
#define NUMBER_OF_SAMPLES 100

/**
   Provide and use a function f that takes x as input and returns the value of sin(2x).
 */
inline double f( const double x )
{
   return std::sin( SINE_MULTIPLIER * x ) ;
}

/**
   Provide and use a function f that takes x as input and returns the value of cos(2x).
 */
inline double g( const double x )
{
   return std::cos( COSINE_MULTIPLIER * x ) ;
}

/**
   Compute the value (x) of the midpoint of each segment and the value (y) of the function f at those midpoints.

   \param x1 [in]
      lower range of the table domain

   \param x2 [in]
      upper range of the table domain
*/
inline double midpoint(const double x1, const double x2)
{
   return ( x1 + x2 )/2.0 ;
}

/**
   Divides the interval (say [-5,5]) into n (=100 say) segments.

   Writes out the values for x, f(x), g(x) in tabular form, three columns tab delimited, with no header rows or any other visual
   separation.

   \param x1 [in]
      lower range of the table domain

   \param x2 [in]
      upper range of the table domain

   \param n [in]
      number of intervals to divide the domain into
*/
void computeAndPrintTable( const double x1, const double x2, const Uint n )
{
   assert( x1 < x2 ) ;
   assert( n != 0 ) ;

   const double intervalWidth{(x2 - x1)/n} ;
   double x = midpoint( x1, x1 + intervalWidth ) ;
   
   for ( Uint i{0} ; i < n ; i++, x += intervalWidth )
   {
      const double y{f( x )} ;
      const double z{g( x )} ;
      std::cout << x << "\t" << y << "\t" << z << "\n" ;
   }

   // done: flush the stream.
   std::cout << std::endl ;
}

/** exit code for successful exectution */
#define RC_SUCCESS      0
/** exit code when -help (or bad option is supplied) */
#define RC_HELP         1
/** exit code if there's a parse error */
#define RC_PARSE_ERROR  2

/** print the usage string for the program for --help (or unrecognized options)
 */
void showHelpAndExit()
{
   std::cerr << "usage: lissajous [--number=n|-n n] [-lower=x1|-l x1] [--upper=x2] [--help]" << std::endl ;

   std::exit( RC_HELP ) ;
}

/**
  Parse command line arguments and invoke the table generating function.
 */
int main( int argc, char ** argv )
{
   Uint n{NUMBER_OF_SAMPLES} ;
   double x1{LOWER_INTERVAL_BOUND} ;
   double x2{UPPER_INTERVAL_BOUND} ;
   int c{0} ;
   int line{0} ;

   const struct option long_options[] = {
     { "help",   0, NULL, 'h' },
     { "number", 1, NULL, 'n' },
     { "lower",  1, NULL, 'l' },
     { "upper",  1, NULL, 'u' },
     { NULL,     0, NULL, 0   }
   } ;

   try {
      while ( -1 != ( c = getopt_long( argc, argv, "hn:l:u:", long_options, NULL ) ) )
      { 
         switch ( c )
         {
            case 'n' :
            {
               line = __LINE__ ;
               n = strToUint( optarg ) ;

               break ;
            }
            case 'l' :
            {
               line = __LINE__ ;
               x1 = std::stod( optarg ) ;

               break ;
            }
            case 'u' :
            {
               line = __LINE__ ;
               x2 = std::stod( optarg ) ;

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

      std::exit( RC_PARSE_ERROR ) ;
   }

   computeAndPrintTable( x1, x2, n ) ;

   return RC_SUCCESS ;
}
