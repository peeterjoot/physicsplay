#include <iostream>

struct physical
{
   double c{ 1.0 }    ;  ///< wave speed

   physical( const double cv ) { throw 3 ; }

   physical( const double cv, const int m ) : physical{cv} { std::cout << "won't get here\n" ; }
} ;

int main()
try
{
   physical p{5} ;

   return 0 ;
}
catch (...) {
   return 1 ;
}
