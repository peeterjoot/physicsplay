//#include <regex>
#include <regex.h>
#include <stdlib.h>
#include <stdio.h>

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

void posixre_transform( regex_t * pRe, const char * input )
{
   constexpr size_t N{3} ;
   regmatch_t m[N] {} ;

   int rc = regexec( pRe, input, N, m, 0 ) ;

   if ( rc && (rc != REG_NOMATCH) )
   {
      posixre_error( pRe, rc ) ;
   }

   if ( !rc )
   {
      printf( "'%s' -> ", input ) ;
      int len ;
      len = m[2].rm_eo - m[2].rm_so ; printf( "'%.*s ", len, &input[ m[2].rm_so ] ) ;
      len = m[1].rm_eo - m[1].rm_so ; printf( "%.*s'\n", len, &input[ m[1].rm_so ] ) ;
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

#if 0
   const char * pattern = "(\\S+)\\s+(\\S+)" ;
   //const char * pattern = R"((\S+)\s+(\S+))" ;
   //const char * pattern = "(.*?) (.*)" ;
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
