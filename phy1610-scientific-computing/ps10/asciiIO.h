/** \file asciiIO.h
 */
#if !defined phy1610_asciiIO_h_included
#define phy1610_asciiIO_h_included

#include "iohandler.h"
#include <fstream>

/**
   Write (s, j, x[i], rho[i]) tuples to an ascii file, where j is the global domain index of the point, and
   s \in [0,...) is the timestep index.
 */
class asciiIO : public iohandlerImplementation
{
public:
   /**
      \param fileBaseName [in]
         Create an ascii file fileBaseName + ".out"

      \param size [in]
         mpi size

      \param rank [in]
         mpi rank

      \param writeTimes [in]
         See iohandler::iohandler
    */
   asciiIO( const std::string &   fileBaseName,
            const int             size,
            const int             rank,
            const bool            writeTimes ) ;

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
      Close the file stream.
    */
   ~asciiIO( ) ;
private:

   std::ofstream        m_file ;
   std::vector<float>   m_times ;         ///< The (s*dt) points in time that the output data is written out.
} ;

#endif
