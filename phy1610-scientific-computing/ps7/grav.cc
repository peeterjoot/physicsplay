/** \file grav.cc
  */
#include "integers.h"
#include <iostream>
#include <string>
#include <getopt.h>
#include "returncodes.h"
#include "ratData.h"
#include <fstream>
#include <cassert>
#include "stdoutfilestream.h"
#include <boost/exception/diagnostic_information.hpp>

/** print the usage string for the program for --help (or unrecognized options)
 */
void showHelpAndExit()
{
   std::cerr << "usage: grav\n" 
      "\t[--ratpath=p|-r p]\n"
      "\t[--help]" << std::endl ;

   std::exit( (int)RETURNCODES::HELP ) ;
}

/**
   Parse arguments and run the driver.
 */
int main( int argc, char ** argv )
{
   int c{0} ;
   int line{0} ;
   std::string ratPath{RATPATH} ;

   constexpr struct option longOptions[]{
     { "help",           0, NULL, 'h' },
     { "ratpath",        1, NULL, 'r' },
     { NULL,             0, NULL, 0   }
   } ;

   try {
      while ( -1 != ( c = getopt_long( argc, argv, "hr:", longOptions, NULL ) ) )
      { 
         switch ( c )
         {
            case 'r' :
            {
               line = __LINE__ ;
               ratPath = optarg ;

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
      ratData data ;
      
      data.open( ratPath, "GWprediction.rat" ) ;
   } 
   catch (boost::exception & e)
   {
      std::string s = boost::diagnostic_information( e ) ;
      std::cout << s << std::endl ;

      return (int)RETURNCODES::EXCEPTION ;
   }

   return (int)RETURNCODES::SUCCESS ;
}
