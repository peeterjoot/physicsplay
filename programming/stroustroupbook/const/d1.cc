struct physical
{
   static constexpr double x2{ +26.0 } ;  ///< right most x value
} ;
constexpr double physical::x2 ;

int main()
{
   physical p ;

   return p.x2 ;
}
