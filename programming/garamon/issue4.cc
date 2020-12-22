#include <e3ga/Mvec.hpp>
#include <iostream>
using namespace std;
using namespace e3ga;
using multivector = Mvec<double>;

void issue4()
{
   const multivector e1 = ::e1<double>();
   const multivector e2 = ::e2<double>();

   multivector mv1;
   multivector mv2(mv1);
   multivector mv3;

   mv1 = 5*e1 -5*e2;
   mv1[E12] = 42.0;
   mv2[E1] = mv1[E2];
   mv2[scalar] = 42.0;

   if(mv1 == mv2){}
cout << "okay\n";
   if(mv1 != mv2){}
cout << "dead by now.\n";
}

int main()
{
   issue4();

   return 0;
}
