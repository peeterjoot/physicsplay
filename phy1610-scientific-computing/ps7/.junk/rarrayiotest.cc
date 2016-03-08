// from the problem set writup, modified to compile.

#include <fstream>
#include <rarray>
#include <rarrayio>
#include <complex>

using namespace std ;

int main() {
   // open the file
   ifstream f("GWprediction.rat");
   // create empty arrays
   rarray<double,1> times;
   rarray<complex<double>,1> signal;
   // read in the signal
   f >> times;
   f >> signal;
}
