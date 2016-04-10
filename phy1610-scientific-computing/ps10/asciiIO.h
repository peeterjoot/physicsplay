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
   asciiIO( const std::string &   fileBaseName,
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

   ~asciiIO( ) ;
private:

   std::ofstream m_file ;
} ;

#endif
