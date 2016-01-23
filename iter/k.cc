#include <iostream>

struct data
{
   float n ;

   void compute()
   {
     n = n + 2 ;
   }

   float fetch() const
   {
     return n ; 
   }

   data() : n(3)
   {
   }

   class iterator 
   {
      data * itr;
      int count ;

   public:

      explicit iterator(data* nd) 
         : itr(nd), count(0)
      { 
      }

      // Default construct gives end.
      explicit iterator( const int n )
         : itr(nullptr), count(n)
      { 
      }

      iterator& operator++ () // Pre-increment
      {
         itr->compute() ;
         count++ ;
         return *this;
      }

      bool operator != ( iterator & rhs)
      {
         return count != rhs.count;
      }

      float operator* () const
      {
         return itr->fetch() ;
      }
   } ;
} ;

int main()
{
   data d ;
   data::iterator i(&d) ;
   data::iterator end(5) ;

   for ( ; i != end ; ++i )
   {
      std::cout << *i << std::endl ;
   }
   
   return 0 ;
}
