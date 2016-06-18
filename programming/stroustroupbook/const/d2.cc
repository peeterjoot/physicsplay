struct physical
{
   double c{ 1.0 }    ;  ///< wave speed
   double tau{ 20.0 } ;  ///< damping time
   double x1{ -26.0 } ;  ///< left most x value
   double x2{ +26.0 } ;  ///< right most x value

   physical( const double cv ) : c{cv} {}
   physical( const double x1v, const double x2v ) : x1{x1v}, x2{x2v} {}

   physical( const double cv, const int m ) : physical{cv} { c *= m ; } ;
} ;

int main()
{
   return 0 ;
}
