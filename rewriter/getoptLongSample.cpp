#include <getopt.h> // gnu getopt assumed.
#include <cstdio>   // printf
#include <cstdlib>  // exit

using namespace std ;

void printUsageAndExit( const char * argv0 )
{
   printf( "%s [-Ipath | --include=path] [-Dval | --define=val] [-h | --help] filename.cpp\n"
           "\n"
           "\tExample: %s x.cpp -Ipath1 -Dfoo -Dhoo --include=path2\n"
           , argv0
           , argv0 ) ;

   exit( 1 ) ;
}

int main(int argc, char *argv[])
{
   struct option options[] =
   {
       {"include", 1, 0, 'I'}
      ,{"define", 1, 0, 'D'}
      ,{"help", 1, 0, 'h'}
   } ;

   int c = 0 ;
   int optindex = 0 ;

   while ( ( c = getopt_long(argc, argv, "I:D:h", options, &optindex ) ) != EOF )
   {
      switch (c)
      {
         case 'I':
         {
            printf( "-I : %s\n", optarg ) ;
            break ;
         }
         case 'D':
         {
            printf( "-D : %s\n", optarg ) ;
            break ;
         }

         case 'h':
         default:
         {
            printUsageAndExit( argv[0] ) ;
         }
      }
   }

   if ( optind != (argc - 1) )
   {
      printUsageAndExit( argv[0] ) ;
   }

   printf( "%s\n", argv[optind] ) ;

   return 0 ;
}
