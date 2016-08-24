#include <unordered_map>
#include <string>
#include <iostream>

int main()
{
   std::unordered_map<std::string, int> m { {"hi", 0 }, {"bye", 1} } ;

   for ( auto p : m )
   {
      std::cout << p.first << ", " << p.second << '\n' ;
   }

   return 0 ;
}
