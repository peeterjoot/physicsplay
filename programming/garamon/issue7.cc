#include <e3ga/Mvec.hpp>
#include <iostream>
using namespace std;
using namespace e3ga;
using multivector = Mvec<double>;

void issue7()
{
   const multivector e1 = ::e1<double>();
   const multivector e2 = ::e2<double>();
   const auto e12 = ::e12<double>();

   multivector mv1;
   multivector mv2(mv1);
   multivector mv3;

   mv1 = -3120.65 + 9066.51*e1 + 17022*e2 + 73008.7*e12;
   mv2 = 5*e1 -5*e2;

   cout << "mv1: " << mv1 << endl;
   cout << "mv2: " << mv2 << endl;

   mv3 = mv1.outerPrimalDual(mv2);    // fast version of mv3 = mv1 ^ mv2.dual();
}

int main()
{
   issue7();
   return 0;
}
