/** \file graphicsIO.h
 */
#if !defined phy1610_graphicsIO_h_included
#define phy1610_graphicsIO_h_included

#include "iohandler.h"

/**
   Handle IO for a float x[N] "grid", plus float rho[N] "data", writing out just the local MPI
   domain contributions to those 1D arrays.
 */
class graphicsIO : public iohandlerImplementation
{
public:
   /** prep for plots to follow */
   graphicsIO( ) ;

   /**
      \copydoc iohandlerImplementation::writeMeta
    */
   void writeMeta( const size_t          globalOffset,
                   const size_t          localN,
                   const float * const   localXstart,
                   const float * const   localRhoStart ) ;

   /**
      \copydoc iohandlerImplementation::writeData
    */
   void writeData( const size_t          timestep,
                   const size_t          globalOffset,
                   const size_t          localN,
                   const float * const   localXstart,
                   const float * const   localRhoStart ) ;

   /**
      how much time to sleep between plots.
    */
   void setSleepTime( const int t )
   {
      m_sleepTime = t ;
   }

   /** no-op destructor */
   ~graphicsIO( ) ;
private:

   /**
      Perform the plot for one timestep.  Has the common code for writeMeta and writeData.

      \internal
    */
   void plot( const size_t          localN,
              const float * const   x,
              const float * const   rhoInit,
              const float * const   rho ) ;

   bool           m_openedWindow ; ///< true for cpgbeg success.
   const float *  m_rhoInitStart ; ///< Cache the value passed in during writeMeta
   int            m_sleepTime ;
   int            m_red ;          ///< red colour handle
   int            m_grey ;         ///< grey colour handle
   int            m_white ;        ///< white colour handle
} ;

#endif
