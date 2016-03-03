/**
 \file springmodel.cc
 */
#include "integers.h"
#include <fstream>
#include <cassert>
#include <string>
#include <iostream>
#include <cstdio>
#include <getopt.h>
#include "minimizer.h"
#include "stdoutfilestream.h"
#include "springfunction.h"
#include "gslsolver.cc"
#include "returncodes.h"

/** print the usage string for the program for --help (or unrecognized options)
 */
void showHelpAndExit()
{
   std::cerr
      << "usage: springmodel\n"
         "\t[--file=p|-f p]\n"
         "\t  The path to the output filename.  Stdout will be used if unspecified.\n"
         "\t[--csv|-c [--mass=m|-m m]]\n"
         "\t  Evaluate the minimization function at a\n"
         "\t  set of points in the interval and output a csv format file with these points for plotting.\n"
         "\t[--verbose|-v]\n"
         "\t  Instead of the output required for the problem, show some detailed diagnositic state.\n"
         "\t[--xmax]\n"
         "\t  Show the x position of the largest local min instead of the (default) smallest local min for each value of m in [0,0,5].\n"
         "\t[--fmax]\n"
         "\t  Show E(x_max) for the the largest local min for each value of the mass in [0,0.5]\n"
         "\t[--fmin]\n"
         "\t  Show E(x_min) for the the smallest local min (global min) for each value of the mass in [0,0.5]\n"
         "\t[--fmin]\n"
         "\t  Show the difference between the two local minumums or zero for each value of the mass in [0,0.5]\n"
         "\t[--help]"
      << std::endl ;

   std::exit( (int)RETURNCODES::HELP ) ;
}

extern template
class brent_minimizer<gsl_spring_min_function> ;

/**
   This class collects the gsl minimization function,
   the parameters that define the interval, and the allocated gsl minimizer object.  That
   is everything that we required to run the minimizer for a given mass and interval.
 */
class minimizerstate
{
   gsl_spring_min_function                   m_f ;
   minimizerParameters                       m_params ;
   brent_minimizer<gsl_spring_min_function>  m_minimizer ;

public:      
   /**
      Set the (position) bounds on the minimization interval, and allocate the gsl minimizer object.
    */
   minimizerstate( ) :
      m_f{},
      m_params( m_f.start(), m_f.end() ), 
      m_minimizer( m_f )
   {
   }

   // use complier generated destructor.  No special handling is required.

   /**
      Run the minimizer for a specified mass.
    */
   void run( const double mass, minimizerResults & results )
   {
      m_f.setMass( mass ) ;

      m_minimizer.f_min_all( m_params, results ) ;
   }

   void printFofX( const double mass, unsigned long numPoints, std::ostream & out )
   {
      m_f.setMass( mass ) ;

      double delta = ( m_f.end() - m_f.start() ) / numPoints ;

      for ( double x = m_f.start() ; x < m_f.end() ; x += delta )
      {
         out << x << ", " << m_f( x ) << std::endl ;
      }
   }

   /**
      Returns a value (1/-1) that indicates whether the difference in position between the pair
      of local minimums at a specific mass is non-zero or zero.

      \param m [in]
         Point at which to evaluate this difference.
     */
   double operator() ( const double m )
   {
      minimizerResults results ;

      run( m, results ) ;

      double d = std::abs( results.diff() ) ;

      constexpr double tolerance = 1e-4 ;

      double sign = (d > tolerance) ? 1.0 : -1.0 ;

      // std::cout << "diff( " << m << " ) = " << sign << ": " << d << std::endl ;

      return sign ;
   }

   /**
      This is a gsl solver method for a non-derivative solver.

      \param m [in]
         Point at which to evaluate this difference.

      \param params [in]
         object state required for the calculation.
     */
   static double function( double m, void * params )
   {
      minimizerstate & state = *(minimizerstate*)params ;

      return state( m ) ;
   }
} ;

/**
   Parse arguments and run the driver.
 */
int main( int argc, char ** argv )
{
   int c{0} ;
   int line{0} ;
   double mass{0.1} ;
   unsigned long numMasses{ 25 } ;
   bool verbose{false} ;
   bool showXmin{true} ;
   bool showXmax{false} ;
   bool showFmin{false} ;
   bool showFmax{false} ;
   bool showDiff{false} ;

   // csv related options:
   bool csv{false} ;
   unsigned long numPoints{1000} ;
   std::string filename{} ;

   constexpr struct option long_options[]{
     { "help",           0, NULL, 'h' },
     { "mass",           1, NULL, 'm' },
     { "num",            1, NULL, 'n' },
     { "file",           1, NULL, 'f' },
     { "csv",            0, NULL, 'c' },
     { "xmin",           0, NULL, 'M' },
     { "xmax",           0, NULL, 'N' },
     { "fmin",           0, NULL, 'F' },
     { "fmax",           0, NULL, 'X' },
     { "diff",           0, NULL, 'd' },
     { "verbose",        0, NULL, 'v' },
     { NULL,             0, NULL, 0   }
   } ;

   try {
      while ( -1 != ( c = getopt_long( argc, argv, "hm:f:n:cvMNFdX", long_options, NULL ) ) )
      {
         switch ( c )
         {
            case 'M' :
            {
               showXmin = true ;

               break ;
            }
            case 'N' :
            {
               showXmax = true ;

               break ;
            }
            case 'F' :
            {
               showFmin = true ;

               break ;
            }
            case 'X' :
            {
               showFmax = true ;

               break ;
            }
            case 'd' :
            {
               showDiff = true ;

               break ;
            }
            case 'v' :
            {
               verbose = true ;

               break ;
            }
            case 'c' :
            {
               csv = true ;

               break ;
            }
            case 'f' :
            {
               line = __LINE__ ;
               filename = std::string( optarg ) ;

               break ;
            }
            case 'm' :
            {
               line = __LINE__ ;
               mass = std::stod( optarg ) ;

               break ;
            }
            case 'n' :
            {
               line = __LINE__ ;
               if ( csv )
               {
                  numPoints = std::stoul( optarg ) ;
               }
               else
               {
                  numMasses = std::stoul( optarg ) ;
               }

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

   stdoutOrFileStream fstream( filename ) ;
   std::ostream & out{ fstream.handle() } ;
   minimizerstate state ;

   if ( csv )
   {
      state.printFofX( mass, numPoints, out ) ;
   }
   else
   {
      constexpr auto massLowerBound { 0.0 } ;
      constexpr auto massUpperBound { 0.5 } ;
      double massDelta { (massUpperBound - massLowerBound)/(numMasses-1) } ;

      double m { massLowerBound } ;

      if ( showDiff )
      {
         out << "mass diff\n" ;
      }
      else if ( showFmin )
      {
         out << "mass fmin\n" ;
      }
      else if ( showFmax )
      {
         out << "mass fmax\n" ;
      }
      else if ( showXmax )
      {
         out << "mass xmax\n" ;
      }
      else if ( showXmin )
      {
         out << "mass xmin\n" ;
      }

      for ( unsigned long i = 0 ; i < numMasses ; i++ )
      {
         minimizerResults results ;

         state.run( m, results ) ;

         if ( verbose )
         {
            out << "Mass:\t" << m << "\n" ;

            for ( const auto & r : results.m_rv )
            {
               out << "\tSolving on: [ " << r.m_initial_a << ", " << r.m_initial_b << " ]\n"
                   << "\tIterations:\t" << r.m_iter << "\n"
                   << "\tConverged:\t" << r.m_converged << "\n"
                   << "\tStatus:\t" << r.m_status << " (" << r.m_strerror << ")" << "\n"
                   << "\tMin:\t" << r.m_xmin << " in [ " << r.m_a << ", " << r.m_b << "]\n"
                   << "\tF(Min):\t" << r.m_fmin << "\n"
                   << "\tAbserr (bracket):\t" << r.m_b - r.m_a << "\n"
                   << std::endl ;
            }

            out << std::endl ;
         }
         else
         {
            double v{} ;

            if ( showDiff )
            {
               v = std::abs( results.diff() ) ;
            }
            else if ( showFmin )
            {
               v = results.fmin() ;
            }
            else if ( showFmax )
            {
               v = results.fmax() ;
            }
            else if ( showXmax )
            {
               v = results.xmax() ;
            }
            else if ( showXmin )
            {
               v = results.xmin() ;
            }

            out << m << ' ' << v << std::endl ;
         }

         m += massDelta ;
      }
   }

   /////////////////////////////////////////////////
   //
   // part (c).
   // Find:
   //   The maximum load m, i.e. the value of the mass m at which the two
   //   local minima have the same energy. One way to implement this is to use one
   //   of the GSL root finding algorithms on a function that gives the difference
   //   of the energy values of the two minima, which can be obtained from f_all_min.
   //
   // The value of the maximum load can be printed out to the console.
   //
   constexpr double massInterval[]{ 0.0, 0.5 } ;
   constexpr double maxIter{25} ;
   constexpr double tolerance { 1e-4 } ;

   intervalIterationInputs p( massInterval[0],
                              massInterval[1],
                              maxIter,
                              0,
                              0,
                              tolerance,
                              tolerance ) ;
   intervalIterationResults r ;

   fSolver<minimizerstate> s( state ) ;

   s.iterate( p, r ) ;

   if ( verbose )
   {
      std::cout << "Using " << r.m_solvername << " on: [ " << massInterval[0] << ", " << massInterval[1] << " ]\n"
                << "Iterations:\t" << r.m_iter << "\n"
                << "Converged:\t" << r.m_converged << "\n"
                << "Status:\t" << r.m_status << " (" << r.m_strerror << ")" << "\n"
                << "Root:\t" << r.m_x << "\n"
                << "Interval:\t [ " << r.m_xLo << ", " << r.m_xHi << " ]\n"
                << "Abserr (bracket):\t" << r.m_xHi - r.m_xLo << "\n" << std::endl ;
   }
   else
   {
      std::cout << "Maximum load: " << r.m_x << " (kg)" << std::endl ;
   }

   return (int)RETURNCODES::SUCCESS ;
}
