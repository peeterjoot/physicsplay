#include "matrix.h"
#include <iostream>

int main() {

   matrix m;
   m.set( identity );

   std::cout << m.elem(1,1) << "\n";
   std::cout << m.elem(1,2) << "\n";

   return 0;
}
