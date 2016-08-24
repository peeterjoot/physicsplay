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

   // apparently this is also a valid operator.  Had no idea what it was, but stackoverflow says "pointer to member" dereference:
   //
   // http://stackoverflow.com/questions/38035231/what-is-the-c-operator
   int operator ->*(const foo & f) 
   {
      return blah() + f.blah() ;
   }
} ;

int main()
{
   foo f ;
   foo g{ 7 } ;

   return (f, g) + (f ->* g) ;
}
