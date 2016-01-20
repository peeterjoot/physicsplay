/**
   \file showps5.cc

   Print out the value of the function and it's derivative to plot and verify that it looks right.
 */

#include <iostream>
#include "ps5function.h"

int main()
{
   ps5function f ;

   for ( double x = 0.0 ; x <= 10.0 ; x += 0.01 )
   {
      double y, dy ;

      ps5function::functionAndDerivative( x, &f, &y, &dy ) ; 

      std::cout << x << ", " << y << ", " << dy << std::endl ;
   }

   return 0 ;
}
