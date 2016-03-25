#include <fstream>
using namespace std;
#include <ginac/ginac.h>
using namespace GiNaC;

//#include <ginca/indexed.h>
//#include <ginca/tensor.h>
//#include <ginca/symbol.h>
//#include <ginca/idx.h>
//#include <set>

#if 0
void test1()
{
	symbol x("x"), y("y"), z("z");
	symbol mu("mu") ;

	// do some math

   ex blah = sin(x) * sin(y) + cos(x) * cos(y) ;
   ex lah = sin(x) * sin(y) + cos(x) * cos(x) ;
	ex foo = (sin(x + 2*y) *2 * x * 1 * x * 2 * x)
      + 3*z + 41;
	ex bar = foo + 1;

   cout << latex ;

   cout << "foo: " << foo << endl ;
   cout << "bar: " << bar << endl ;
   cout << "blah: " << blah << endl ;
   cout << "lah: " << lah << endl ;
   cout << "bar + mu: " << bar + mu << endl ;
}
#endif

inline ex generalComplexExponential( const ex & i, const ex & scalar )
{
   return cos(scalar) + i * sin(scalar) ;
}

inline ex complexExponential( const ex & scalar )
{
   return generalComplexExponential( I, scalar ) ;
}

void test2()
{
#if 0

   F 
      &= \sum_{\Bk} e^{i \Bk c t } \inv{V} \int e^{ i \Bk \cdot (\Bx' - \Bx) } F(x', 0) d^3 x' \\
      &= \sum_{\Bk} e^{i \kcap \Abs{\Bk} c t } \inv{V} \int e^{ i \Bk \cdot (\Bx' - \Bx) } F(x', 0) d^3 x' \\

#endif

   symbol kct("\\Abs{\\Bk} c t") ;
   symbol kcap("\\kcap") ;
   symbol k_dot_delta_x("\\Bk \\cdot (\\Bx' - \\Bx)") ;

   ex ikct = I * kct ;

   cout << latex ;
   cout << "e^{ikct}: " << cos(kct) + I * kcap * sin(kct)<< endl ;
   ex e_ikct = generalComplexExponential( I * kcap, kct ) ;
   ex e_ikDeltaX = complexExponential( k_dot_delta_x ) ;

   cout << "e^{i \\Bk c t} = " << e_ikct << endl ;
   cout << "e^{i k . (x'-x)} = " << e_ikDeltaX << endl ;

   ex p = e_ikct * e_ikDeltaX ;
   ex F = symbol("\\EE(x',0)") + I * symbol("\\HH(x',0)") ;
   cout << "e^{i \\Bk c t } e^{i k . (x'-x)} = " << p << endl ;
   cout << "e^{i \\Bk c t } e^{i k . (x'-x)} = " << p.expand() << endl ;
   ex p2 = p * F ;
   cout << "e^{i \\Bk c t } e^{i k . (x'-x)} * F = " << p2.expand() << endl ;

#if 0
//   varidx mu(symbol("mu"), 1) ;
   idx m0(symbol("m0"), 0) ;
   idx m1(symbol("m1"), 1) ;
   idx m2(symbol("m2"), 2) ;
   idx m3(symbol("m3"), 3) ;
   idx m4(symbol("m4"), 4) ;
   ex d0 = dirac_ONE(0) ;
   ex d1 = dirac_ONE(1) ;
   ex d2 = dirac_ONE(2) ;
   ex d3 = dirac_ONE(3) ;
   ex d4 = dirac_ONE(4) ;

//   cout << "g: " << dirac_gamma(m1) << endl ;
   cout << "d1: " << d1 << endl ;
   cout << "d00: " << d0 *d0 << endl ;
   cout << "d11: " << d1 *d1 << endl ;
   cout << "d22: " << d2 *d2 << endl ;
   cout << "d33: " << d3 *d3 << endl ;
   cout << "d44: " << d4 *d4 << endl ;
#endif
}

int main()
{
//   test1() ;
   test2() ;

   return 0 ;
}
