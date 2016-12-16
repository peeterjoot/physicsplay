// from: http://en.cppreference.com/w/cpp/memory/unique_ptr/make_unique
#include <iostream>
#include <memory>
 
struct Vec3
{
   int x{1}, y{3}, z{7} ;

   Vec3() = default ;
//   Vec3() : x{}, y{}, z{} {}
   Vec3(int x_, int y_, int z_) : x(x_), y(y_), z(z_) { }

   friend std::ostream& operator<<(std::ostream& os, Vec3& v) {
      return os << '{' << "x:" << v.x << " y:" << v.y << " z:" << v.z  << '}' ;
   }
} ;
 
int main()
{
   // Use the default constructor.
   std::unique_ptr<Vec3> v1 = std::make_unique<Vec3>() ;
   // Use the constructor that matches these arguments
   std::unique_ptr<Vec3> v2 = std::make_unique<Vec3>(0, 1, 2) ;
   // Create a unique_ptr to an array of 5 elements
   std::unique_ptr<Vec3[]> v3 = std::make_unique<Vec3[]>(5) ;
 
   std::cout << "make_unique<Vec3>():     " << *v1 << '\n'
             << "make_unique<Vec3>(0,1,2): " << *v2 << '\n'
             << "make_unique<Vec3[]>(5):   " << '\n' ;

#if 0
   for ( auto a : v3 )
   {
      std::cout << "    " << a<< '\n' ;
   }
#else
   //for ( int i{} ; i < sizeof(v3)/sizeof(v3[0]) ; i++ )
   for ( int i{} ; i < 5 ; i++ )
   {
      std::cout << "    " << v3[i] << '\n' ;
   }
#endif

   return 0 ;
}
