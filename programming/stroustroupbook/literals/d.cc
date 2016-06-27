#include <string>
#include <iostream>

static_assert( __cplusplus >= 201402L, "require c++14 for string literal suffix" ) ;

using namespace std::literals ;

int main()
{
   std::string hi { "hi\n" } ;
#if 1
   hi += "there"s + "\n" ;
#elif 0
   hi += "there" + "\n" ;
#else
   hi += std::string{"there"} + "\n" ;
#endif

   std::cout << hi ;

   return 0 ;
}

