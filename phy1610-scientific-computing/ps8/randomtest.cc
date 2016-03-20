#include <random>
#include <iostream>

class FairCoin
{
public:
   FairCoin()
      : uniform( 0, 1 )
   {
   }

   void start( int seed )
   {
      engine.seed( seed ) ;
   }

   int toss()
   {
      auto state = uniform( engine ) ;
      return 2 * state - 1 ;
   }

private:
   std::default_random_engine          engine ;
   std::uniform_int_distribution<int>  uniform ;
} ;

class uniformreal
{
public:
   uniformreal()
      : uniform( 0, 1 )
   {
   }

   void start( double seed )
   {
      engine.seed( seed ) ;
   }

   double toss()
   {
      auto state = uniform( engine ) ;
      return 2 * state - 1 ;
   }

private:
   std::default_random_engine              engine ;
   std::uniform_real_distribution<double>  uniform ;
} ;

int main()
{
   //FairCoin c ;
   uniformreal c ;

   for ( int i = 0 ; i < 20 ; i++ )
   {
      std::cout << c.toss() << std::endl ;
   }

   return 0 ;
}
