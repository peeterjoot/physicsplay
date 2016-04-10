/** \file iohandler.cc
 */
#include "netcdfIO.h"

iohandler::iohandler( const cfg             c,
                      const std::string &   fileBaseName,
                      const size_t          N )
   : m_ioHandler(nullptr)
{
   switch ( c )
   {
      case cfg::netcdf:
      {
         m_ioHandler = new netcdfIO( fileBaseName, N ) ;
         break ;
      }
      default:
         throw( "not implemented yet" ) ;
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
