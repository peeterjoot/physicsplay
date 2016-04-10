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

void iohandlerImplementation::writeData( const size_t          timeStepCount,
                                         const size_t          globalOffset,
                                         const size_t          localN,
                                         const float * const   localXstart,
                                         const float * const   localRhostart )
{
}

iohandlerImplementation::~iohandlerImplementation( )
{
}

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
         m_ioHandler = new asciiIO( fileBaseName + "_" + std::to_string( mpirank ) ) ;
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

void iohandler::writeData( const size_t          timeStepCount,
                           const size_t          globalOffset,
                           const size_t          localN,
                           const float * const   localXstart,
                           const float * const   localRhostart )
{
   if ( m_ioHandler )
   {
      m_ioHandler->writeData( timeStepCount,
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

/** close files, handles, ... */
iohandler::~iohandler()
{
   if ( m_ioHandler )
   {
      delete m_ioHandler ;
   }
}
