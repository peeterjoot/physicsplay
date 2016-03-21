/** \file randomtest.cc */
#include <iostream>
#include "randomgenerators.h"

int main()
{
   using FairCoin = RandomIntegers<-1, 2, 1> ;
   using R2 = RandomDiscreteReals<2> ;
   using R3 = RandomReals<> ;

   FairCoin c ;
   R2 r(-0.5, 0.5) ;
   R3 s(-0.5, 0.5) ;

   std::cout << "Random values in {-1,1}\n\n" ;
   for ( int i = 0 ; i < 20 ; i++ )
   {
      std::cout << c.sample() << std::endl ;
   }

   std::cout << "\nRandom values in {-0.5, 0, 0.5}\n\n" ;
   for ( int i = 0 ; i < 20 ; i++ )
   {
      std::cout << r.sample() << std::endl ;
   }

   std::cout << "\nRandom values in [-0.5, 0.5]\n\n" ;
   for ( int i = 0 ; i < 20 ; i++ )
   {
      std::cout << s.sample() << std::endl ;
   }

   return 0 ;
}
