/** \file parseoptions.h
 */
#if !defined phy1610_parseoptions_h_included
#define phy1610_parseoptions_h_included

#include <getopt.h>
#include <cstdlib>
#include <iostream>
#include "returncodes.h"
#include "integers.h"

class parseOptions
{
   const char * m_exeName ;
   Uint         m_nrec ;

   /** print the usage string for the program for --help (or unrecognized options)
    */
   void showHelpAndExit()
   {
      std::cerr
         << "usage: " << m_exeName << "\n"
            "\t[--nrec]\n"
            "\t[--help]"
         << std::endl ;

      std::exit( (int)RETURNCODES::HELP ) ;
   }

public:
   parseOptions( int argc, char ** argv ) : m_exeName{argv[0]}, m_nrec{1}
   {
      int c{0} ;
      int line{0} ;

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
                  m_nrec = strToUint( optarg ) ;

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
            << "option: -" << (char)c << '\n'
            << "argument: " << optarg << '\n'
            << std::endl ;

         std::exit( (int)RETURNCODES::PARSE_ERROR ) ;
      }
   }

   Uint nrec() const
   {
      return m_nrec ;
   }
} ;

#endif
