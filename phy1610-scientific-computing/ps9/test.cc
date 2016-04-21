/**
   \file test.cc

   standalone simple test cases.
 */
#define BOOST_TEST_MAIN
//#define BOOST_TEST_NO_MAIN
#define BOOST_TEST_MODULE test

#include "boosttest.h" // include this first to override assert()
#include "myexceptions.h"
#include "arrayIOwriter.h"
#include <fstream>
#include <vector>
#include <omp.h>

struct dummyMeta {
   int x{1} ;
   int y{2} ;
   int numThreads{ omp_get_max_threads() } ;
} ;

// http://stackoverflow.com/a/15024257/189270
void checkFileEquality( const std::string & name1, const std::string & name2 )
{
   std::ifstream ifs1( name1, std::ios::binary ) ;
   std::ifstream ifs2( name2, std::ios::binary ) ;

   std::istream_iterator<char> b1( ifs1 ), e1 ;
   std::istream_iterator<char> b2( ifs2 ), e2 ;

   BOOST_REQUIRE_EQUAL_COLLECTIONS( b1, e1, b2, e2 ) ;
}

BOOST_AUTO_TEST_CASE( testWriterSmallArray )
{
   arrayIOwriter fserial( "serial", arrayIOwriter::IO_method::serial ) ;
   arrayIOwriter fthreaded( "threaded", arrayIOwriter::IO_method::threaded ) ;
   arrayIOwriter fmultifile( "multifile", arrayIOwriter::IO_method::multifile ) ;

   dummyMeta meta ;
   auto size{(size_t)meta.numThreads*2} ;
   std::vector<int> x(size) ;
   std::vector<int> data(size) ;
   for ( size_t i{0} ; i < size ; i++ )
   {
      x[i] = i/2 ;

      data[i] = i * 2 ;
   }

   fserial.writeMetaData( &meta, sizeof(meta) ) ;
   fthreaded.writeMetaData( &meta, sizeof(meta) ) ;
   fmultifile.writeMetaData( &meta, sizeof(meta) ) ;

   fserial.writeMetaData( &x[0], sizeof(x[0])*size ) ;
   fthreaded.writeMetaData( &x[0], sizeof(x[0])*size ) ;
   fmultifile.writeMetaData( &x[0], sizeof(x[0])*size ) ;

   // This is a test of the small IO codepath.  Expect just one non-metadata file for all methods
   fserial.writeData( &data[0], sizeof(data[0]), std::max(meta.numThreads-1,1) ) ;
   fthreaded.writeData( &data[0], sizeof(data[0]), std::max(meta.numThreads-1,1) ) ;
   fmultifile.writeData( &data[0], sizeof(data[0]), std::max(meta.numThreads-1,1) ) ;

   // for testing test code:   
   if ( 0 )
   {
      int more{3} ;

      fmultifile.writeMetaData( &more, sizeof(more) ) ;
   }

   checkFileEquality( "serial00000.out", "threaded00000.out" ) ;
   checkFileEquality( "serial00000.out", "multifile00000.out" ) ;

   checkFileEquality( "serial00001.out", "threaded00001.out" ) ;
   checkFileEquality( "serial00001.out", "multifile00001.out" ) ;
}

BOOST_AUTO_TEST_CASE( testWriterLargerArray )
{
   arrayIOwriter fserial( "serial", arrayIOwriter::IO_method::serial ) ;
   arrayIOwriter fthreaded( "threaded", arrayIOwriter::IO_method::threaded ) ;
   arrayIOwriter fmultifile( "multifile", arrayIOwriter::IO_method::multifile ) ;

   dummyMeta meta ;
   auto size{(size_t)meta.numThreads*20} ;
   std::vector<int> x(size) ;
   std::vector<int> data(size) ;
   for ( size_t i{0} ; i < size ; i++ )
   {
      x[i] = i/2 ;

      data[i] = i * 2 ;
   }

   fserial.writeMetaData( &meta, sizeof(meta) ) ;
   fthreaded.writeMetaData( &meta, sizeof(meta) ) ;
   fmultifile.writeMetaData( &meta, sizeof(meta) ) ;

   fserial.writeMetaData( &x[0], sizeof(x[0])*size ) ;
   fthreaded.writeMetaData( &x[0], sizeof(x[0])*size ) ;
   fmultifile.writeMetaData( &x[0], sizeof(x[0])*size ) ;

   fserial.writeData( &data[0], sizeof(data[0]), size ) ;
   fthreaded.writeData( &data[0], sizeof(data[0]), size ) ;
   fmultifile.writeData( &data[0], sizeof(data[0]), size ) ;

   // for testing test code:   
   if ( 0 )
   {
      int more{3} ;

      fmultifile.writeMetaData( &more, sizeof(more) ) ;
   }

   checkFileEquality( "serial00000.out", "threaded00000.out" ) ;
   checkFileEquality( "serial00000.out", "multifile00000.out" ) ;

   int rc = system( "cat serial*out > sall.out" ) ;
   BOOST_REQUIRE( 0 == rc ) ;
   rc = system( "cat threaded*out > tall.out" ) ;
   BOOST_REQUIRE( 0 == rc ) ;
   rc = system( "cat multifile*out > mall.out" ) ;
   BOOST_REQUIRE( 0 == rc ) ;

   checkFileEquality( "sall.out", "tall.out" ) ;
   checkFileEquality( "sall.out", "mall.out" ) ;
}

#if 0
// didn't realize that omp_get_num_threads() is only active in a parallel block, and my code that
// cached that outside of a parallel block wasn't working because of this.
// I really wanted omp_get_max_threads().  It seemed to me that this was only happening in my boost
// code, so I thought it was somehow an interaction with boost test, and wanted to see what was happening
// in main before boost was invoked.  This was a way of checking that, but is now unneccessary.
// using this requires not defining BOOST_TEST_MAIN, but also defining BOOST_TEST_NO_MAIN
bool init_function()
{
    return true ;
}

int main( int argc, char *argv[] )
{
   std::cout << omp_get_num_threads() << std::endl ;
   std::cout << omp_get_max_threads() << std::endl ;

   //return 0 ;
   return boost::unit_test::unit_test_main(init_function, argc, argv) ;
}
#endif
