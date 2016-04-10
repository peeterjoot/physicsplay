/** \file iohandler.h
 */
#if !defined phy1610_iohandler_h_included
#define phy1610_iohandler_h_included

#include <string>

class iohandlerImplementation
{
public:
   virtual void writeMeta( const size_t          globalOffset,
                           const size_t          localN,
                           const float * const   localXstart,
                           const float * const   localRhoStart ) = 0 ;

   /**
      \param timeStepCount [in]
         A value >=1 representing the count of which timestep this is, with 1 being the first.

      \param globalOffset [in]
         Location of the data to be written relative to global domain, with 0 representing
         the first data element.

      \param localN [in]
         Number of local domain elements to write.

      \param localRhostart [in]
         Local domain location of the data to write.
    */
   virtual void writeData( const size_t          timeStepCount,
                           const size_t          globalOffset,
                           const size_t          localN,
                           const float * const   localRhostart ) = 0 ;

   virtual ~iohandlerImplementation( ) = 0 ;
} ;

/**
   A method to handle IO for a float x[N] "grid", plus float rho[N] "data", writing out just the local MPI
   domain contributions to those 1D arrays.

   The data itself will be written out using graphics, ascii, or netcdf as specified.
 */
class iohandler
{
public: 

   enum class cfg { graphics  ///< pgplot based graphical display
                    ,ascii    ///< Ascii output to a file
//                    ,binary   ///< Binary output to a file
                    ,netcdf   ///< Write raw (binary) data to a netcdf file
                  } ;

   /** open files handles and other stuff depending on the configuration mode. */
   iohandler( const cfg c, const std::string & fileBaseName, const size_t N ) ;

   /** close files, handles, ... */
   ~iohandler() ;
private:

   iohandlerImplementation * m_ioHandler ;
} ;

#endif
