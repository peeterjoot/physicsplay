/** \file iohandler.cc
 */
#include "netcdfIO.h"
#include "graphicsIO.h"
#include "asciiIO.h"
#include <string>

void iohandlerImplementation::writeMeta( const size_t          globalOffset,
                                         const size_t          localN,
                                         const float * const   localXstart,
                                         const float * const   localRhoStart )
{
}

void iohandlerImplementation::writeData( const float           time,
                                         const size_t          globalOffset,
                                         const size_t          localN,
                                         const float * const   localXstart,
                                         const float * const   localRhostart )
{
}

void iohandlerImplementation::close( )
{
}

iohandlerImplementation::~iohandlerImplementation( )
{
}

iohandler::iohandler( const cfg             c,
                      const std::string &   fileBaseName,
                      const size_t          N,
                      const int             mpisize,
                      const int             mpirank,
                      const bool            writeTimes,
                      const std::string &   params )
   : m_ioHandler(nullptr)
{
   switch ( c )
   {
      case cfg::netcdf:
      {
         m_ioHandler = new netcdfIO( fileBaseName, N, mpisize, mpirank, writeTimes, params ) ;
         break ;
      }
      case cfg::ascii:
      {
         m_ioHandler = new asciiIO( fileBaseName, mpisize, mpirank, writeTimes ) ;
         break ;
      }
      case cfg::graphics:
      {
         m_ioHandler = new graphicsIO( ) ;
         break ;
      }
      default:
         break ;
         // no-op.
   }
}

void iohandler::writeData( const float           time,
                           const size_t          globalOffset,
                           const size_t          localN,
                           const float * const   localXstart,
                           const float * const   localRhostart )
{
   if ( m_ioHandler )
   {
      m_ioHandler->writeData( time,
                              globalOffset,
                              localN,
                              localXstart,
                              localRhostart ) ;
   }
}

void iohandler::writeMeta( const size_t          globalOffset,
                           const size_t          localN,
                           const float * const   localXstart,
                           const float * const   localRhoStart )
{
   if ( m_ioHandler )
   {
      m_ioHandler->writeMeta( globalOffset,
                              localN,
                              localXstart,
                              localRhoStart ) ;
   }
}

void iohandler::setSleepTime( const int t )
{
   graphicsIO * g = dynamic_cast<graphicsIO *>( m_ioHandler ) ;

   if ( g )
   {
      g->setSleepTime( t ) ;
   }
}

/** close files, handles, ... */
void iohandler::close()
{
   if ( m_ioHandler )
   {
      m_ioHandler->close() ;
   }
}

/** last resort closure of files, handles, ... */
iohandler::~iohandler()
{
   if ( m_ioHandler )
   {
      delete m_ioHandler ;
   }
}
