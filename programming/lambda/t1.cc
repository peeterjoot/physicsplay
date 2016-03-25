#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;
 
int main()
{
   vector<int> numbers { 1, 2, 3, 4, 5, 10, 15, 20, 25, 35, 45, 50 };

   for_each(numbers.begin(), numbers.end(), [] (int y)
   {
       cout << y << endl;
   });

   return 0 ;
}
