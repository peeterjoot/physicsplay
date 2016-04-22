/** \file bassert.cc */
#include <boost/exception/diagnostic_information.hpp>
#include "myexceptions.h"

int main( int argc, char ** argv )
{
   try {
      ASSERT_DATA_INT( argc == 0, argc ) ;
   }
   catch ( boost::exception & e )
   {
      auto s { boost::diagnostic_information( e ) } ;
      std::cout << s << std::endl ;

      return 1 ;
   }

   return 0 ;
}
