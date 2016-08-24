namespace myproject
{
   inline namespace V2
   {
      struct X {
         int x ;
         int y ;
      } ;
      void foo( const X & ) ;
   }

   namespace V1
   {
      struct X {
         int x ;
      } ;

      void foo( const X & ) ;
   }
}

