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

int m0()
{
   matrix m1 = f() ;

   return m1.size() ;
}

int m1()
{
   matrix m1 = f() ;
   matrix m2 { f() } ;

   return m1.size() + m2.size() ;
}

int main()
{
   return m0() ;
}

#if 0
#include "m2.cc"
#endif
