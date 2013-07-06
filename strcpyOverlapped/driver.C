#include <string.h>
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <assert.h>
#include <sys/types.h>

void initializeBuffer( char * const buf, const size_t size )
{
#if 0
   for ( int i = 0 ; i < size ; i++ )
   {
      buf[ i ] = rand() % 128 ;

      if ( !isprint( buf[ i ] ) )
      {
         buf[ i ] = ' ' ;
      }
   }
#else
   memset( buf, ' ', size ) ;
#endif
}

#define BUF_MULTIPLICITY 3

char * randomizeString( char * const buf, const char * const src, const size_t size )
{
   for ( int i = 0 ; i < BUF_MULTIPLICITY ; i++ )
   {
      memcpy( buf + i * size, src, size ) ;
   }
   buf[ size * BUF_MULTIPLICITY - 1 ] = 0 ;

   int max ;
   int min ;

   for ( ; ; )
   {
      max = rand() % ( size - 1 ) ;

      if ( max > 1 )
      {
         min = rand() % ( max - 1 ) ;

         break ;
      }
      else
      {
         continue ;
      }
   }

   buf[ max + size ] = 0 ;
   return &buf[ min + size ] ;
}

void systemStrcpy( char * const dest, const char * const src ) ;

//#define OVERLAPPED
inline bool pred( const ssize_t diff, const size_t len )
{
#if defined OVERLAPPED
   return ( diff <= len ) ;

   #define VERBOSE 1
#else
   return ( diff > len ) ;

   #define VERBOSE 0
#endif
}

int main( int argc, char ** argv )
{
   #define BUF_SIZE 16
   #define TOTAL_COPY_CHECKS 1024
   char mem[ BUF_SIZE ] ;
   char buf[ BUF_SIZE * BUF_MULTIPLICITY ] ; 
   char copy[ BUF_SIZE ] ; 
   int numCopies = 0 ;
   int iterations = 0 ;
   int verbose = VERBOSE ;
   initializeBuffer( mem, sizeof(mem) ) ;

   for ( ; numCopies < TOTAL_COPY_CHECKS ; iterations++ )
   {
RETRY:
      char * src = randomizeString( buf, mem, BUF_SIZE ) ;
      size_t len = strlen( src ) ;
      assert( len < BUF_SIZE ) ;

      strcpy( copy, src ) ;

      char * dest ;
      ssize_t diff ;

      for ( int n = 0 ; ; )
      {
#if defined OVERLAPPED
         dest = &buf[ rand() % ( sizeof(buf) - 1 ) ] ;
#else
         dest = &buf[ BUF_SIZE + rand() % ( BUF_SIZE - 1 ) ] ;
#endif
         diff = dest - src ;

//#define REQUIRE_DEST_LESSER_THAN_SRC
#if defined REQUIRE_DEST_LESSER_THAN_SRC
         if ( diff > 0 )
         {
            continue ;
         }
#endif
         if ( diff < 0 )
         {
            diff = -diff ;
         }

         if ( pred( diff, len ) && (&dest[len + 1] < &buf[BUF_SIZE * BUF_MULTIPLICITY -1]) )
         {
            break ;
         }

         if ( ++n > 3 )
         {
            goto RETRY ;
         }
      }

      if ( verbose )
      {
         printf( "buf:\t[%p, %p]\n"
                 "dest:\t[%p, %p]\n"
                 "src:\t[%p, %p]\n"
                 "strlen + 1:\t%u\n"
                 "diff:\t%d\n",
                 buf,
                 buf + sizeof(buf) - 1,
                 dest,
                 dest + len + 1,
                 src,
                 src + len + 1,
                 (unsigned)len + 1,
                 (int)diff ) ;
      }
      else
      {
         printf( "." ) ;

         if ( (0 == (numCopies % 80)) && numCopies )
         {
            printf( "\n" ) ;
         }
      }

      numCopies++ ;

      systemStrcpy( dest, src ) ;
      if ( 0 != strcmp( dest, copy ) )
      {
         printf( "pattern: '%s'\n"
                 "dest: '%s'\n"
                 "src: %p\n"
                 "dest: %p\n"
                 "diff: %d\n"
                 "strlen + 1: %u\n",
                 copy,
                 dest,
                 src,
                 dest,
                 (int)diff,
                 (unsigned)len + 1 ) ;

         break ;
      }
   }

   printf( "\nDONE\n" ) ; 

   return iterations ;
}
