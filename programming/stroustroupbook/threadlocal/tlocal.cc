#include <thread>
#include <vector>
#include <stdio.h>
//#include <iostream>
#include <string.h>
#include <pthread.h>

void body( )
{
   constexpr size_t sz {256} ;
// doesn't work with xcode 7 (should for xcode 8)
   static thread_local char * estr = new char[sz] ;

   for ( int loops = 0 ; loops < 1000 ; loops++ )
   {
      for ( int i = 1 ; i < 100 ; i++ )
      {
         strerror_r( i, estr, sz ) ;

         printf( "i: %d (%s)\n", i, estr ) ;
//         std::cout << "i: " << i << estr << '\n' ;
      }
   }
}

int main()
{
   std::vector<std::thread> a(10) ;

   for ( auto & t : a )
   {
      t = std::thread( body ) ;
   }

   for ( auto & t : a )
   {
      t.join() ;
   }

   return 0 ; 
}
