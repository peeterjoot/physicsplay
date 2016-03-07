/** \file ratData.cc */
#include "stdoutfilestream.h"
#include "ratData.h"
#include "rarrayio"

/**
   helper function to fully qualify a file given a directory and the filename within that dir.

   restrictions: This function is Unix specific.
 */
inline std::string fullyQualifyPathWithDirectory( const std::string directoryName, const std::string fileName )
{
   if ( (fileName[0] != '/') && (directoryName != "") )
   {
      return directoryName + "/" + fileName ;
   }
   else
   {
      return fileName ;
   }
}

void ratData::open( const std::string ratPath, const std::string filename )
{
   std::string qualPath = fullyQualifyPathWithDirectory( ratPath, filename ) ;

   // open the file
   std::ifstream f{} ;

   openStreamForReadOrThrow( qualPath, f ) ;

   // read in the signal
   f >> m_times ;
   f >> m_signal ;
}
