#include <string>

struct F
{
   std::string s{} ;
   
   F( int n ) : s( n, 'a' ) {}

#if 1
   F() = default ;
#endif
} ;

F x ;
