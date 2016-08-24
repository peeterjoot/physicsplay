#include "foo.h"

T foo()
{
   return std::make_tuple( 1.0, "blah", 3 ) ;
}

S bar()
{
   return { 1.0, "blah", 3 } ;
}
