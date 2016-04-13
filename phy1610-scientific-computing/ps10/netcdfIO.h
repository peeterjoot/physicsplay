/** \file netcdfIO.h
 */
#if !defined phy1610_netcdfIO_h_included
#define phy1610_netcdfIO_h_included

#include "iohandler.h"
#include <vector>

/**
   Handle IO for a float x[N] "grid", plus float rho[N] "data", writing out just the local MPI
   domain contributions to those 1D arrays.
 */
class netcdfIO : public iohandlerImplementation
{
public:
   /**
      \param fileBaseName [in]
         Write to fileBaseName + ".nc"

      \param N [in]
         Dimensions of the arrays to write.

      \param params [in]
         A string representation of some of the input and derived parameters for the run.
    */
   netcdfIO( const std::string &   fileBaseName,
             const size_t          N,
             const int             rank,
             const std::string &   params ) ;

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
   void writeData( const float           time,
                   const size_t          globalOffset,
                   const size_t          localN,
                   const float * const   localXstart,
                   const float * const   localRhoStart ) ;

   /**
      \copydoc iohandlerImplementation::close
    */
   void close() ;

   /**
      Close the netcdf file created if that was successful.
    */
   ~netcdfIO( ) ;
private:

   bool                 m_opened ;        ///< True if nc_create succeeded.
   int                  m_ncid ;          ///< File descriptor for the netcdf file.
   int                  m_xDimId ;        ///< Dimension identifier for the (grid) position dimension.
   int                  m_tDimId ;        ///< Dimension identifier for the time dimension.
   int                  m_rhoVarId ;      ///< Variable identifier for the rho array.
   int                  m_xVarId ;        ///< Variable identifier for the x array.
   int                  m_atTimesVarId ;  ///< Variable identifier for the array of timestep times (s * dt).

   /**
      Let the MPI rank 0 task write out all the times that data has been written.
    */ 
   void writeTimes( ) ;

   void internalClose( const bool isErrorCodePath ) ;
} ;

#endif
