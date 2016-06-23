#include "matrix.h"

matrix f() ;
void g( matrix & ) ;

matrix mg( {4, 5, 6} ) ;

int m0()
{
   matrix x1 = f() ;
   matrix x2 { std::move( mg ) } ;

   return x1.rows() + x2.rows() ;
}

int m1()
{
   matrix x1 = f() ;
   matrix x2 { f() } ;

   return x1.rows() + x2.rows() ;
}

int m2()
{
   matrix x1(0) ;
   g( x1 ) ;

   return x1.rows() ;
}

int main()
{
   std::cout << mg << '\n' ;

//   return 0 ;
   return m0() + m2() ;
}

#if defined INLINE_M2
#include "m2.cc"
#endif
