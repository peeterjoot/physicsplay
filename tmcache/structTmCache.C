#include <time.h>
#include <errno.h>
#include <sys/time.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <assert.h>

static time_t g_refTimeInSec ;
static struct tm g_structTmForRefTime ;

void cacheStructTm()
{
   struct timeval currentTimeStamp ;
   struct tm * pTm ;
   int rc ;

   rc = gettimeofday( &currentTimeStamp, 0 ) ;
   if ( rc )
   {
      printf( "gettimeofday error: %d (%s)\n", errno, strerror(errno) ) ;
      abort() ;
   }

   pTm = localtime_r( &currentTimeStamp.tv_sec, &g_structTmForRefTime ) ;
   if ( NULL == pTm )
   {
      printf( "localtime_r error: %d (%s)\n", errno, strerror(errno) ) ;
      abort() ;
   }

   g_structTmForRefTime.tm_sec = 0 ;
   g_structTmForRefTime.tm_min = 0 ;
   g_structTmForRefTime.tm_hour = 0 ;

   g_refTimeInSec = mktime( &g_structTmForRefTime ) ;
}

void localTimeFromCached( const time_t timeInSec, struct tm * const pTm )
{
   assert( timeInSec >= g_refTimeInSec ) ;
   time_t secondsSinceLastCached = timeInSec - g_refTimeInSec ;

   #define SECONDS_IN_A_DAY (60*60*24)
   bool needToRefreshCachedValue ;
   needToRefreshCachedValue = ( !g_refTimeInSec || (secondsSinceLastCached > SECONDS_IN_A_DAY) ) ;

#if 0
   if ( needToRefreshCachedValue )
   {
      // NOTE: care to update cached value would be required.  Possibilities include keeping this in the pGp
      cacheStructTm() ;
      secondsSinceLastCached = timeInSec - g_refTimeInSec ;
   }
#else
   assert( !needToRefreshCachedValue ) ;
#endif

   *pTm = g_structTmForRefTime ;
   pTm->tm_sec = secondsSinceLastCached % 60 ;
   time_t rem = secondsSinceLastCached / 60 ;
   pTm->tm_min = rem % 60 ;
   pTm->tm_hour = rem / 60 ;
}

int main()
{
   int rc ;
   struct tm t1 ;
   struct tm t2 ;
   struct timeval currentTimeStamp ;

   cacheStructTm() ;

   sleep( 3 ) ;

   rc = gettimeofday( &currentTimeStamp, 0 ) ;
   if ( rc )
   {
      printf( "gettimeofday error: %d (%s)\n", errno, strerror(errno) ) ;
      abort() ;
   }

   localTimeFromCached( currentTimeStamp.tv_sec, &t1 ) ;

   printf( "hack way:\n"
           "tm_sec = %d\n"
           "tm_min = %d\n"
           "tm_hour = %d\n"
           "tm_mday = %d\n"
           "tm_mon = %d\n"
           "tm_year = %d\n"
           "tm_wday = %d\n"
           "tm_yday = %d\n"
           "tm_isdst = %d\n",
           t1.tm_sec,
           t1.tm_min,
           t1.tm_hour,
           t1.tm_mday,
           t1.tm_mon,
           t1.tm_year,
           t1.tm_wday,
           t1.tm_yday,
           t1.tm_isdst ) ;

   localtime_r( &currentTimeStamp.tv_sec, &t2 ) ;

   printf( "real way:\n"
           "tm_sec = %d\n"
           "tm_min = %d\n"
           "tm_hour = %d\n"
           "tm_mday = %d\n"
           "tm_mon = %d\n"
           "tm_year = %d\n"
           "tm_wday = %d\n"
           "tm_yday = %d\n"
           "tm_isdst = %d\n",
           t2.tm_sec,
           t2.tm_min,
           t2.tm_hour,
           t2.tm_mday,
           t2.tm_mon,
           t2.tm_year,
           t2.tm_wday,
           t2.tm_yday,
           t2.tm_isdst ) ;

   return 0 ;
}
