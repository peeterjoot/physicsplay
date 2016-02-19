#include <iostream>

using namespace std ;

int main()
{
   // Can zero initialize all elements in c++11 with the allocation:
   int * y = new int[3] {} ;

   cout << y[0] << endl ;
   cout << y[1] << endl ;
   cout << y[2] << endl ;

   // and can explicit initialize all elements:
   int * x = new int[3] {3,4,5} ;

   cout << x[0] << endl ;
   cout << x[1] << endl ;
   cout << x[2] << endl ;

   // but this doesn't 3-initialize all the elements, and seems to be either {3,0,0} or {3, undef, undef}
   // (not sure which)
   int * z = new int[3] {3} ;

   cout << z[0] << endl ;
   cout << z[1] << endl ;
   cout << z[2] << endl ;

   return 0 ;
}
