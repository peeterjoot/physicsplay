// vim: ai:ts=3:sw=3
#include <unordered_map>
#include <string>
#include <memory>
#include <iostream>

struct foo {
   int x{};

   foo( int v ) : x(v) {}
};

struct map {
   std::unordered_map<std::string, std::unique_ptr<foo> > m;

   int rename( const std::string & o, const std::string & n ) {
      auto f = m.find( o );
      if ( f == m.end() )
         return 1;

      try {
         auto c = m.emplace( n, nullptr );
         bool ok = c.second;

         if ( !ok ) {
            return 3; // target already exists.
         } else {
	    c.first->second = std::move( f->second );
            m.erase( f );
         }
      } catch (std::exception & e) {
         return 2;
      }

      return 0;
   }
};

int main()
{
   map ma;
   ma.m.emplace( "hi", std::make_unique<foo>(3) );
   ma.m.emplace( "bye", std::make_unique<foo>(4) );

   ma.rename( "hi", "foo" );

   for ( auto & p : ma.m ) {
//      if ( p.second ) {
         std::cout << p.first << ", " << p.second->x << '\n' ;
//      }
//      else {
//         std::cout << p.first << ", (null)\n";
//      }
   }

   return 0 ;
}
