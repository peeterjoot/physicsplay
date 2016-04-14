/** \file graphicsIO.cc */
#include <cpgplot.h>
#include "graphicsIO.h"
#include <unistd.h>

graphicsIO::graphicsIO( )
   : iohandlerImplementation( -1, -1 ) // don't need mpi state for graphics IO.
   , m_openedWindow( false )
   , m_rhoInitStart( nullptr )
{
   // 
   // check for success for the initial begin command, so lots of noise
   // isn't generated for subsequent plot APIs.
   //
   if ( cpgbeg( 0, "/xwindow", 1, 1 ) == 1 )
   {
      m_openedWindow = true ;

      cpgask( 0 ) ;
      m_red = 2 ; cpgscr( m_red, 1., 0., 0. ) ;
      m_grey = 3 ; cpgscr( m_grey, .2, .2, .2 ) ;
      m_white = 4 ; cpgscr( m_white, 1.0, 1.0, 1.0 ) ;
   }
}

void graphicsIO::plot( const size_t          localN,
                       const float * const   x,
                       const float * const   rhoInit,
                       const float * const   rho )
{
   if ( !m_openedWindow )
   {
      return ;
   }

   double localX1 = x[ 1 ] ;
   double localX2 = x[ localN ] ;

   cpgsls( 1 ) ;
   cpgslw( 6 ) ;
   cpgsci( m_white ) ;
   cpgslw( 2 ) ;
   cpgenv( localX1, localX2, 0., 0.25, 0, 0 ) ;
   cpglab( "x", "rho", "Wave test" ) ;
   cpgsls( 1 ) ;
   cpgslw( 6 ) ;
   cpgsci( m_white ) ;
   cpgline( localN + 2, x, rhoInit ) ;
   cpgsls( 2 ) ;
   cpgslw( 12 ) ;
   cpgsci( m_red ) ;
   cpgline( localN + 2, x, rho ) ;
}

void graphicsIO::writeData( const float           timeIgnored,
                            const size_t          globalOffsetIgnored,
                            const size_t          localN,
                            const float * const   localXstart,
                            const float * const   localRhoStart )
{
   if ( !m_openedWindow )
   {
      return ;
   }

   cpgbbuf( ) ;
   cpgeras( ) ;

   plot( localN,
         &localXstart[-1],
         m_rhoInitStart,
         &localRhoStart[-1] ) ;

   cpgebuf( ) ;

   if ( m_sleepTime )
   {
      sleep( m_sleepTime ) ;
   }
}

void graphicsIO::writeMeta( const size_t          globalOffsetIgnored,
                            const size_t          localN,
                            const float * const   localXstart,
                            const float * const   localRhoStart )
{
   plot( localN,
         &localXstart[-1],
         &localRhoStart[-1],
         &localRhoStart[-1] ) ;

   m_rhoInitStart = localRhoStart ;
}

void graphicsIO::close( )
{
}

graphicsIO::~graphicsIO( )
{
}
