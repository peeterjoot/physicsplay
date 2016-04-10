/** \file netcdfIO.h
 */
#if !defined phy1610_netcdfIO_h_included
#define phy1610_netcdfIO_h_included

#include "iohandler.h"

/**
   Handle IO for a float x[N] "grid", plus float rho[N] "data", writing out just the local MPI
   domain contributions to those 1D arrays.
 */
class netcdfIO : public iohandlerImplementation
{
public:
   netcdfIO( const std::string &   fileBaseName,
             const size_t          N ) ;

   void writeMeta( const size_t          globalOffset,
                   const size_t          localN,
                   const float * const   localXstart,
                   const float * const   localRhoStart ) ;

   void writeData( const size_t          timestep,
                   const size_t          globalOffset,
                   const size_t          localN,
                   const float * const   localRhoStart ) ;

   ~netcdfIO( ) ;
private:

   bool  m_opened ;
   int   m_ncid ;
   int   m_xDimId ;
   int   m_tDimId ;
   int   m_rhoVarId ;
   int   m_xVarId ;
} ;

#endif
