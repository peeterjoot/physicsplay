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
   graphicsIO( const std::string &   fileBaseName,
               const size_t          N ) ;

   void writeMeta( const size_t          globalOffset,
                   const size_t          localN,
                   const float * const   localXstart,
                   const float * const   localRhoStart ) ;

   void writeData( const size_t          timestep,
                   const size_t          globalOffset,
                   const size_t          localN,
                   const float * const   localXstart,
                   const float * const   localRhoStart ) ;

   ~graphicsIO( ) ;
private:

   void plot( const size_t          localN,
              const float * const   x,
              const float * const   rhoInit,
              const float * const   rho ) ;

   const float *  m_rhoInitStart ; ///< Cache the value passed in during writeMeta
   int            m_red ;
   int            m_grey ;
   int            m_white ;
} ;

#endif
