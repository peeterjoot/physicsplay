// vim: ai:ts=3:sw=3
#include <unordered_map>
#include <string>
#include <memory>
#include <iostream>

struct foo
{
   int x;

   foo( int v ) : x(v) {}
};

int main()
{
   std::unordered_map<std::string, std::unique_ptr<foo> > m;
   m.emplace( "hi", std::make_unique<foo>(3) );
   m.emplace( "bye", std::make_unique<foo>(4) );
   auto i = m.emplace( "hi", nullptr );
   bool ok = i.second;
   if ( ok ) {
      std::cout << "hi doesn't exist -- don't expect this.\n"; 
   }
   else {
      std::cout << "hi already exists -- expect this.\n"; 
   }

   auto j = m.emplace( "foo", nullptr );
   ok = j.second;
   if ( ok ) {
      std::unique_ptr pt = std::make_unique<foo>(5);
      j.first->second = std::move( pt );
   }

   for ( auto & p : m )
   {
      std::cout << p.first << ", " << p.second->x << '\n' ;
   }

   return 0 ;
}
