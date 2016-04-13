/** \file iohandler.h
 */
#if !defined phy1610_iohandler_h_included
#define phy1610_iohandler_h_included

#include <string>
#include <vector>

/**
   Low level IO writer for a float x[N] "grid", plus float rho[N] "data", writing out just the local MPI
   domain contributions to those 1D arrays.
 */
class iohandlerImplementation
{
public:
   /** allocate any resources required, open files, ...
    */
   virtual void writeMeta( const size_t          globalOffset,
                           const size_t          localN,
                           const float * const   localXstart,
                           const float * const   localRhoStart ) = 0 ;

   /**
      \param time [in]
         The "point in time" (s*dt) for which the data is being output.

      \param globalOffset [in]
         Location of the data to be written relative to global domain, with 0 representing
         the first data element.

      \param localN [in]
         Number of local domain elements to write.

      \param localXstart [in]
         Local domain location of the grid points to write in ascii mode.

         For ascii mode IO it is assumed that 
         localXstart[0] is the location of the first non-ghost cell grid value, and that 
         localXstart[-1] and localXstart[localN] are both accessible (the ghost cell values.)

      \param localRhostart [in]
         Local domain location of the data to write.

         For ascii mode IO it is assumed that 
         localRhostart[0] is the location of the first non-ghost cell grid value, and that 
         localRhostart[-1] and localRhostart[localN] are both accessible (the ghost cell values.)
    */
   virtual void writeData( const float           time,
                           const size_t          globalOffset,
                           const size_t          localN,
                           const float * const   localXstart,
                           const float * const   localRhostart ) = 0 ;

   /**
      Close any required files, handles, or resources if required.
    */
   virtual void close() = 0 ;

   /** Free any remaining resources after close() has been called.
    */
   virtual ~iohandlerImplementation( ) = 0 ;

   inline iohandlerImplementation( const int mpi_rank ) : m_times(), m_outStepCount{0}, m_rank{mpi_rank}
   {
   }

protected:
   std::vector<float>   m_times ;         ///< The (s*dt) points in time that the output data is written out.
   size_t               m_outStepCount ;  ///< The T variable value at which this write is occuring.
   int                  m_rank ;          ///< mpi rank for the calling task.
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
                    ,netcdf   ///< Write raw (binary) data to a netcdf file
                    ,noop     ///< No IO, graphics, ...
                  } ;

   /**
      Open files handles and other stuff depending on the configuration mode.
  
      \param c [in]
          How to do the IO.
 
      \param fileBaseName [in]
          Filename for the IO.  mpirank may be appended to this in some IO modes.
 
      \param N [in]
          Dimensions of the float "grid" and 1D data arrays to write.

      \param mpirank [in]
          A value in the [0, mpi_size) range.

      \param paramsInfo [in]
          A string representation of some of the input and derived parameters for the run.
    */
   iohandler( const cfg             c,
              const std::string &   fileBaseName,
              const size_t          N,
              const int             mpirank,
              const std::string &   paramsInfo ) ;

   /** \copydoc iohandlerImplementation::writeData */
   void writeData( const float           time,
                   const size_t          globalOffset,
                   const size_t          localN,
                   const float * const   localXstart,
                   const float * const   localRhostart ) ;

   /** \copydoc iohandlerImplementation::writeMeta */
   void writeMeta( const size_t          globalOffset,
                   const size_t          localN,
                   const float * const   localXstart,
                   const float * const   localRhoStart ) ;

   /**
      for graphics.  set the sleep time between plots.
    */
   void setSleepTime( const int t ) ;

   /**
      Close any required files, handles, or resources if required.
    */
   void close() ;

   /** Free any remaining resources after close() has been called.
    */
   ~iohandler() ;
private:

   iohandlerImplementation * m_ioHandler ;
} ;

#endif
