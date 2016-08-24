#include <memory>
#include <thread>

struct T
{
   int x{1} ;    
   int y{2} ;    
   int z{3} ;    

   ~T()
   {
      printf( "destroy\n" ) ;
   }
} ;

using Tp = std::shared_ptr<T> ;

void bar( Tp p )
{
   printf( "bar: %ld: %d %d %d\n", p.use_count(), p->x, p->y, p->z ) ;
}

void foo( Tp p )
{
   printf( "foo: %ld: %d %d %d\n", p.use_count(), p->x, p->y, p->z ) ;

   std::thread t( bar, p ) ;
   t.join() ;
}

int main()
{
   std::shared_ptr<T> p = std::make_shared<T>() ;

   foo( p ) ;

   return 0 ;
}
