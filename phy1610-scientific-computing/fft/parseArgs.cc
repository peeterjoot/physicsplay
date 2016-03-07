#include <iostream>
#include <getopt.h>
#include "returncodes.h"

/** print the usage string for the program for --help (or unrecognized options)
 */
void showHelpAndExit( char * argv0 )
{
   std::cerr
      << "usage: " << argv0 << "\n"
         "\t[--infile]"
         "\t[--outfile]"
         "\t[--help]"
      << std::endl ;

   std::exit( (int)RETURNCODES::HELP ) ;
}

void parseArgs( int argc, char ** argv, std::string & infile, std::string outfile )
{
   int c{0} ;
   int line{0} ;

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
               showHelpAndExit( argv[0] ) ;
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
}
