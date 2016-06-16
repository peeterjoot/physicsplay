#include <iostream>

enum class x { v = 1, w } ;
enum y { vv = 1, ww } ;

int main()
{
   x e1 = {} ;
   y e2 = {} ;
   std::cout << (int)e1 << '\n' ;
   std::cout << e2 << '\n' ;

   return 0 ;
}
