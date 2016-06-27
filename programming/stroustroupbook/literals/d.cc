#include <string>
#include <iostream>

using namespace std::literals ;

int main()
{
   std::string hi { "hi\n" } ;
   hi += "there"s + "\n" ;

   std::cout << hi ;

   return 0 ;
}

