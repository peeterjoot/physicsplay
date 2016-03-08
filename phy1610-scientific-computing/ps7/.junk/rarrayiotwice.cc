// What happens if we write into an rarray twice?

#include <fstream>
#include <iostream>
#include <rarray>
#include <rarrayio>
#include <complex>

using namespace std ;

int main() {
   ifstream f("x.rat") ;
   ifstream g("y.rat") ;

   rarray<double,1> a ;

   f >> a ;
   cout << "x.rat: " << a.size() << endl ;
   cout << a << endl ;

   g >> a ;
   cout << "y.rat: " << a.size() << endl ;
   cout << a << endl ;

   return 0 ;
}
