#include <cstdlib>
#include <iostream>

extern "C"
void normalexit()
{
   std::cout << "normalexit\n" ;
}

extern "C"
void quickCexit()
{
   std::cout << "quickCexit\n" ;
}

void quickCPPexit()
{
   std::cout << "quickCPPexit\n" ;
}

class X
{
public:
   ~X()
   {
      std::cout << "X::~X()\n" ;
   }
} x ;

int main()
{
   atexit( normalexit ) ;
   std::at_quick_exit( quickCexit ) ;
   std::at_quick_exit( quickCPPexit ) ;

   std::quick_exit( 3 ) ;

   return 0 ;
}
