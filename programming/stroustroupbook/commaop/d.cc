struct foo
{
   int m ;

   foo( int v = {} ) : m{v} {}

   int blah( ) const
   {
      return m + 3 ;
   }

   int operator,(const foo & f) 
   {
      return blah() + f.blah() ;
   }

   int operator ->*(const foo & f) 
   {
      return blah() + f.blah() ;
   }
} ;
} ;

int main()
{
   foo f ;
   foo g{ 7 } ;

   //return f, g ;
   return f ->* g ;
}
