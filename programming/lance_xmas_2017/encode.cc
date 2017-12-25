#include <bitset>
#include <iostream>

int main()
{
   const char x[]{"MerryChristmasDadILoveYou"};

   for ( auto c : x )
   {
      std::string s = std::bitset< 8 >( c ).to_string(); // string conversion

      std::cout << c << ' ' << s << "\n" ;
   }

   return 0;
}
