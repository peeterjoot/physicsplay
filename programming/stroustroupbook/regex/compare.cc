#include <regex>
#include <regex.h>
#include <stdlib.h>

void posixre_error( regex_t * pRe, int rc )
{
   char buf[ 128 ] ;

   regerror( rc, pRe, buf, sizeof(buf) ) ;

   fprintf( stderr, "regerror: %s\n", buf ) ;
   exit( 1 ) ;
}

void posixre_compile( regex_t * pRe, const char * expression )
{
   int rc = regcomp( pRe, expression, REG_EXTENDED ) ;
   if ( rc )
   {
      posixre_error( pRe, rc ) ;
   }
}

void posixre_transform( regex_t * pRe, const char * string )
{
   constexpr size_t N{3} ;
   regmatch_t m[N] ;

   int rc = regexec( pRe, string, N, m, 0 ) ;

   if ( rc && (rc != REG_NOMATCH) )
   {
      posixre_error( pRe, rc ) ;
   }

   if ( !rc )
   {
      printf( "0: %*s\n", (int)(m[0].rm_eo - m[0].rm_so), &string[ m[0].rm_so ] ) ;
      printf( "1: %*s\n", (int)(m[1].rm_eo - m[1].rm_so), &string[ m[1].rm_so ] ) ;
      printf( "2: %*s\n", (int)(m[2].rm_eo - m[2].rm_so), &string[ m[2].rm_so ] ) ;
   }
}

void posixre_free( regex_t * pRe )
{
   regfree( pRe ) ;
}

int main()
{
   regex_t re ;

   const char * strings[] { "hi bye", "hello world", "why now", "one two" } ;

#if 0 // works on Linux, but not on Mac:
   const char * pattern = "(\S+)\s+(\S+)" ;
#else
   const char * pattern = "([^[:space:]]+)[[:space:]]+([^[:space:]]+)" ;
#endif

   posixre_compile( &re, pattern ) ;

   for ( auto s : strings )
   {
      posixre_transform( &re, s ) ;
   }

   posixre_free( &re ) ;

   return 0 ;
}
