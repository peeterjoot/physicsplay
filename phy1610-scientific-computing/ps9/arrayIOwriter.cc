/** \file arrayIOwriter.cc
 */

#include "arrayIOwriter.h"
#include "myexceptions.h"
#include <unistd.h>
#include <cassert>
#include <omp.h>
#include <boost/exception/exception.hpp>
#include <boost/exception/errinfo_errno.hpp>
#include <boost/exception/errinfo_file_name.hpp>
#include <boost/exception/info.hpp>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <errno.h>

constexpr arrayIOwriter::fileHandleType invalidFileHandle{-1} ;

arrayIOwriter::fileHandleType arrayIOwriter::internalOpen( const unsigned fileSequenceNumber )
{
   char filename[ 1024 ] ;

   snprintf( filename, sizeof(filename), "%s%05u.out", m_filePathAndBaseName.c_str(), fileSequenceNumber ) ;

   int fd = open( filename, O_CREAT | O_WRONLY | O_TRUNC, S_IRUSR | S_IWUSR ) ;
   if ( -1 == fd )
   {
      int e = errno ; // save errno in case std::string makes any (allocation) syscalls.

      // have to make a copy because the filename buffer is on the stack and we
      // wouldn't want to return a pointer to that when the frame goes out of scope.
      std::string n( filename ) ;

      BOOST_THROW_EXCEPTION(
            file_open_error()
               << name_info( n )
               << boost::errinfo_errno( e ) ) ;
   }

   return fd ;
}

arrayIOwriter::arrayIOwriter( const std::string &   filePathAndBaseName,
                              const IO_method       how )
   : m_numThreads{ omp_get_max_threads() }
   , m_how{how}
   , m_metaDataFd{invalidFileHandle}
   , m_fd{invalidFileHandle}
   , m_currentOffset{0}
   , m_nextFileNumber{0}
   , m_filePathAndBaseName( filePathAndBaseName )
{
   m_metaDataFd = internalOpen( m_nextFileNumber ) ;
   m_nextFileNumber++ ;

   if ( IO_method::multifile != m_how )
   {
      m_fd = internalOpen( m_nextFileNumber ) ;
   }
}

arrayIOwriter::writePartitionInfo::writePartitionInfo( const void * const   start,
                                                       const size_t         totalBytes,
                                                       const int            numThreads,
                                                       const int            threadnum )
   : m_batchSizeBytes{ totalBytes / numThreads }
   , m_startpos{nullptr}
{

   // give the last thread anything left over
   if ( (threadnum + 1) == numThreads )
   {
      m_batchSizeBytes += (totalBytes % numThreads) ;
   }

   assert( m_batchSizeBytes ) ; // these cases were implicitly handled before this function was called.

   m_startpos = (char *)start + m_batchSizeBytes * threadnum ;
}

void arrayIOwriter::internalWrite( const int            fd,
                                   const void * const   start,
                                   const size_t         bytes )
{
   ssize_t n = write( fd, start, bytes ) ;

   if ( -1 == n )
   {
      int e = errno ;

      BOOST_THROW_EXCEPTION(
            file_write_error()
               << boost::errinfo_errno( e )
               << file_descriptor_info( fd ) ) ;
   }
   else if ( n != (ssize_t)bytes )
   {
      BOOST_THROW_EXCEPTION(
            file_write_error()
               << write_info( bytes )
               << write_res_info( n ) ) ;
   }
}

void arrayIOwriter::internalPwrite( const int            fd,
                                    const void * const   start,
                                    const size_t         bytes,
                                    const off_t          offset )
{
   ssize_t n = pwrite( fd, start, bytes, offset ) ;

   if ( -1 == n )
   {
      int e = errno ;

      BOOST_THROW_EXCEPTION(
            file_write_error()
               << boost::errinfo_errno( e )
               << write_addr_info( start )
               << write_info( bytes )
               << write_offset_info( offset )
               << file_descriptor_info( fd ) ) ;
   }
   else if ( n != (ssize_t)bytes )
   {
      BOOST_THROW_EXCEPTION(
            file_write_error()
               << write_addr_info( start )
               << write_info( bytes )
               << write_offset_info( offset )
               << write_res_info( n ) ) ;
   }
}

void arrayIOwriter::writeMetaData( const void * const   start,
                                   const size_t         numBytes )
{
   internalWrite( m_metaDataFd, start, numBytes ) ;
}

void arrayIOwriter::writeData( const void * const   start,
                               const size_t         elementSize,
                               const size_t         numElements )
{
   if ( IO_method::serial == m_how )
   {
      internalWrite( m_fd, start, elementSize * numElements ) ;
   }
   else if ( IO_method::threaded == m_how )
   {
      if ( (numElements <= (size_t)m_numThreads) )
      {
         internalPwrite( m_fd, start, elementSize * numElements, m_currentOffset ) ;
      }
      else
      {
         #pragma omp parallel
         {
            int threadnum{ omp_get_thread_num() } ;

            writePartitionInfo p( start, elementSize * numElements, m_numThreads, threadnum ) ;

            internalPwrite( m_fd, p.m_startpos, p.m_batchSizeBytes, m_currentOffset + p.m_batchSizeBytes * threadnum ) ;
         }
      }

      m_currentOffset += elementSize * numElements ;
   }
   else if ( IO_method::multifile == m_how )
   {
      // If we aren't writing more elements than numThreads, use a single serial IO and just one file.
      if ( (numElements <= (size_t)m_numThreads) )
      {
         if ( -1 == m_fd )
         {
            m_fd = internalOpen( m_nextFileNumber ) ;
         }

         internalWrite( m_fd, start, elementSize * numElements ) ;
      }
      else
      {
         #pragma omp parallel
         {
            int threadnum{ omp_get_thread_num() } ;

            writePartitionInfo p( start, elementSize * numElements, m_numThreads, threadnum ) ;

            int fd = internalOpen( threadnum + m_nextFileNumber ) ;

            internalWrite( fd, p.m_startpos, p.m_batchSizeBytes ) ;

            internalClose( fd, true ) ;
         }

         m_nextFileNumber += m_numThreads ;
      }
   }
}

void arrayIOwriter::internalClose( const int    fd,
                                   const bool   throwOnError )
{
   if ( -1 != fd )
   {
      int rc = close( fd ) ;

      if ( (-1 == rc) && throwOnError )
      {
         int e = errno ;

         BOOST_THROW_EXCEPTION(
               file_close_error()
                  << boost::errinfo_errno( e )
                  << file_descriptor_info( fd ) ) ;
      }
   }
}

arrayIOwriter::~arrayIOwriter()
{
   internalClose( m_metaDataFd, false ) ;
   internalClose( m_fd, false ) ;
}
