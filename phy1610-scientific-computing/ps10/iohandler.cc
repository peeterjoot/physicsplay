/** \file iohandler.cc
 */
#include "netcdfIO.h"
#include <string>

iohandler::iohandler( const cfg             c,
                      const std::string &   fileBaseName,
                      const size_t          N,
                      const int             mpirank )
   : m_ioHandler(nullptr)
{
   switch ( c )
   {
      case cfg::netcdf:
      {
         m_ioHandler = new netcdfIO( fileBaseName, N ) ;
         break ;
      }
      case cfg::ascii:
      {
         m_ioHandler = new asciiIO( fileBaseName + "_" + std::to_string( mpirank ), N ) ;
         break ;
      }
      case cfg::graphics:
         throw( "not implemented yet" ) ;
      default:
         // no-op.
   }
}

/** close files, handles, ... */
iohandler::~iohandler()
{
   if ( m_ioHandler )
   {
      delete m_ioHandler ;
   }
}
