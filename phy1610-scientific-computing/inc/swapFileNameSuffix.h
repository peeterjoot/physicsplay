/** \file swapFileNameSuffix.h

   File suffix operations.
 */
#if !defined phy1610_swapFileNameSuffix_h_included
#define phy1610_swapFileNameSuffix_h_included

#include <string>

/**
   Implements a file suffix swap operation, of the (perl) form:

      $f =~ s/\.cc$/.o/ ;

   Example:
      replaceFileSuffix( "blah.cc", "cc", "o" ) 
 */
std::string replaceFileSuffix( const std::string & filename, const char * const oldSuffix, const char * const newSuffix ) ;

#endif
