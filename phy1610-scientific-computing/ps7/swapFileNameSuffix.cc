/** \file swapFileNameSuffix.cc
  */
#include "swapFileNameSuffix.h"
#include "myexceptions.h"
#include <regex>
#include <boost/exception/exception.hpp>
#include <boost/exception/info.hpp>

std::string replaceFileSuffix( const std::string & filename, const char * const oldSuffix, const char * const newSuffix )
{
   std::string expr{ R"((.*)\.)" + std::string(oldSuffix) + "$" } ;
   std::regex reg{ expr } ;
   std::smatch m ;
   std::string outFileName{} ;

   if ( !std::regex_match( filename, m, reg ) )
   {
      BOOST_THROW_EXCEPTION( 
            regex_match_error() 
               << match_info( filename )
               << re_info( expr ) ) ;
   }

   outFileName = m[1].str() + "." + newSuffix ;

   return outFileName ;
}

