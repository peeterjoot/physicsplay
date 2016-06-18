/** \file arrayIOwriter.h
 */
#if !defined phy1610_arrayIOwriter_h_included
#define phy1610_arrayIOwriter_h_included

#include <vector>
#include <unistd.h>
#include "integers.h"

/**
   A helper class for binary file IO of array data.

   Three IO methods are implemented, as specified in the assignment, but have been modified slightly:

   - The IO is split between a metadata file and timestep data file(s)
   - The IO is done in binary mode.

   1) IO_method::serial

      Serial IO to a metadata file and a timestep data file.

      The binary format used will contain all the data available in the original text output.  The metadata portion
      of the output contains

         struct metaData
         {
            int nper ;
            int numPoints ;
            float x[numPoints] ;
            float times[] ;
         } ;

      and the data files are just

         float rho[]

      values.

      Notes:
      - The nsteps value wasn't output in the original text format.
      - The original text format also wrote the x[] array each timestep iteration.

   2) IO_method::threaded

      Parallel IO using a single file, but multiple IO writer threads.

   3) IO_method::multifile

      Parallel IO using multiple files where each thread writes at most one array per file.
      These files will be indexed numerically so that the serial IO file data can be recovered
      by cat'ting all the files on the command line.
 */
class arrayIOwriter
{
public:
   using fileHandleType = int ;

   /**
      IO options for
    */
   enum class IO_method
   {
      serial,
      threaded,
      multifile,
      noop
   } ;

   /**
      \param filePathAndBaseName [in]
         Files with the names "filePathAndBaseName[NNNNN].out" will be created.

      \param how [in]
         Specify the IO method to use.
    */
   arrayIOwriter( const std::string &   filePathAndBaseName,
                  const IO_method       how ) ;

   /**
      Write header data.
    */
   void writeMetaData( const void * const   start,
                       const size_t         numBytes ) ;

   /**
      write one or more array elements to a file or files depending on the IO_method in effect.
    */
   void writeData( const void * const   start,
                   const size_t         elementSize,
                   const size_t         numElements ) ;

   /**
      close any open file descriptors.  Does not throw.
    */
   ~arrayIOwriter( ) ;

private:
   int               m_numThreads ;          ///< number of openmp threads available.
   IO_method         m_how ;                 ///< How should the IO be performed?
   fileHandleType    m_metaDataFd ;          ///< The file descriptor used for the metadata IO.

   fileHandleType    m_fd ;                  ///< The file descriptor used for IO_method::threaded and IO_method::serial
   size_t            m_currentOffset{} ;       ///< The offset of the next timestep data to write (Used for IO_method::threaded.)

   unsigned          m_nextFileNumber{} ;      ///< For multifile, the numeric sequence number for the next file to be created.
   std::string       m_filePathAndBaseName ; ///< The output filename (and/or path) base.  A numeric sequence number and a .out suffix will be appended.

   /** open a file

      \param fileSequenceNumber [in]
         open a file of the form "%s%05u.out" or "%s.out" depending on the IO_method in effect.

      \internal
    */
   fileHandleType internalOpen( const unsigned fileSequenceNumber ) ;

   /** write bytes.  Throws on error */
   static void internalWrite( const fileHandleType   fd,
                              const void * const     start,
                              const size_t           bytes ) ;

   static void internalPwrite( const fileHandleType   fd,
                               const void * const     start,
                               const size_t           bytes,
                               const off_t            offset ) ;

   static void internalClose( const fileHandleType   fd,
                              const bool             throwOnError ) ;

   struct writePartitionInfo
   {
      size_t   m_batchSizeBytes{} ;
      char *   m_startpos{} ;

      writePartitionInfo( const void * const   start,
                          const size_t         numBytes,
                          const int            numThreads,
                          const int            threadNum ) ;
   } ;
} ;

#endif
