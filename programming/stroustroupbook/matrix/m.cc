#include "matrix.h"

matrix f() ;
void g( matrix & ) ;

matrix mg( {4, 5, 6} ) ;

int m0()
{
   std::cout << "m0() cons: x1\n" ;
   matrix x1 = f() ;
   std::cout << "m0() cons (w/ move from mg): x2\n" ;
   matrix x2 { std::move( mg ) } ;

   return x1.rows() + x2.rows() ;
}

int m1()
{
   // neither of these do move operations (not move assignment, nor move construction), but perhaps that's because
   // the compiler is also doing return value optimization, and constructing these in place in the stack storage
   // location of &x1, and &x2:
   matrix x1 = f() ;
   matrix x2 { f() } ;

   return x1.rows() + x2.rows() ;
}

int m2()
{
   std::cout << "m2() cons: x1 (0x0)\n" ;
   matrix x1(0) ;
   std::cout << "m2() call g( x1 )\n" ;
   g( x1 ) ;

   return x1.rows() ;
}

int main()
{
   std::cout << mg << '\n' ;

//   return 0 ;
//   return m0() + m2() ;
   return m1() ;
}

#if defined INLINE_M2
#include "m2.cc"
#endif
