#include "matrix.h"

#if 0
std::ostream & operator <<( std::ostream & o, const matrix & m )
{
   o << "sz: " << m.sz
     << ", e.sz: " << m.e.size() 
     << '\n' ;

/*
   unsigned i = 0 ;
   const char * sep = ' ' ;
   for ( const auto & e : m.e )
   {
      o << e << sep ; 

      if ( i && ((i+1) % m.e.size() == 0)
      {
         sep = '\n' ;
      }
      else
      {
         sep = ' ' ;
      }
   }
*/

   return o ;
}
#endif

matrix f() ;
void g( matrix & ) ;

int m0()
{
   matrix x1 = f() ;

   return x1.size() ;
}

int m1()
{
   matrix x1 = f() ;
   matrix x2 { f() } ;

   return x1.size() + x2.size() ;
}

int m2()
{
   matrix x1(0) ;
   g( x1 ) ;

   return x1.size() ;
}

int main()
{
   return m0() + m2() ;
}

#if 0
#include "m2.cc"
#endif
