/**
   \file tanhTable.cc

   A program that generates a table of data. 

   The table should have two columns, one column with x values ranging from -2.0 to 2.0, and a second column with values y=tanh(2x). 
*/
#include <cmath>
#include <cassert>
#include <iostream>
#include <cstring>
#include <cstdlib>
#include <getopt.h>

#include "integers.h"
#include "returncodes.h"

/**
   Provide and use a function f that takes x as input and returns the value of tanh(2x).
 */
inline double f(const double x)
{
   return std::tanh( 2 * x ) ;
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
   Divides the interval [-2,2] into n=100 segments.

   Write out the x and y values in tabular form (i.e. two-column ascii text), either to a file or to screen.

   Note: the problem description doesn't say to print any sort of header row, or special delimiters.  I've used a tab delimiter and no header row.

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
      std::cout << x << "\t" << y << '\n' ;
   }

   // done: flush the stream.
   std::cout << std::endl ;
}

/** print the usage string for the program for --help (or unrecognized options)
 */
void showHelpAndExit()
{
   std::cerr << "usage: tanhTable [--number=n|-n n] [-lower=x1|-l x1] [--upper=x2] [--help]" << std::endl ;

   std::exit( (int)RETURNCODES::HELP ) ;
}

/**
  Parse command line arguments and invoke the table generating function.
 */
int main( int argc, char ** argv )
{
   Uint n{100} ;
   double x1{-2.0} ;
   double x2{+2.0} ;
   int c ;
   int line{0} ;

   constexpr struct option long_options[]{
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

   computeAndPrintTable( x1, x2, n ) ;

   return (int)RETURNCODES::SUCCESS ;
}
