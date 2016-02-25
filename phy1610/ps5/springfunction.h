/** \file springfunction.h
 */
#if !defined phy1610_springfunction_h_included
#define phy1610_springfunction_h_included

/**
   The function object for the gsl minimization code.
 */
class gsl_spring_min_function
{
   double a ; ///< J (energy scale)
   double b ; ///< m (length scale)
   double c ; ///< N/m (spring constant)
   double d ; ///< m(maximum spring extension)
   double f ; ///< dimensionless (stiffness at maximum extension)
   double g ; ///< m/s^2 (gravitational accelleration).
   double m ; ///< mass (kg)

   // pre-calculate some of the products and ratios required to evaluate the function:
   double c1 ;
   double c2 ;
   double c3 ;

   /**
      Kinetic energy of the spring function
    */
   double es( const double x ) const
   {
      double xdSq = ( x - d ) * ( x - d ) ;
      double xbSq = ( x - b ) * ( x - b ) ;
      return c1 /x + c2 / xdSq - a * std::exp( c3 * xbSq ) ;
   }

   /**
      Potential energy of the spring function
    */
   double ew( const double x )
   {
      return - g * m * x ;
   }

public:
   /**
      constructor.  set physical parameters for the energy functions
    */
   gsl_spring_min_function( const double mass ) :
      a{1},
      b{0.1},
      c{100},
      d{0.5},
      f{2500},
      g{9.8},
      m{mass},
      c1{a * b},
      c2{a * d * d/f},
      c3{- c/(2 * a)}
   {
   }

   /**
      Evaluate the energy of the spring at the specified point.
    */
   double operator() ( const double x ) const
   {
      return es( x ) + ew( x ) ;
   }

   /**
      Total energy of the spring function to pass to the gsl minimization code.
    */
   static double function( double x, void *param )
   {
      gsl_spring_min_function & p = *(gsl_spring_min_function *)param ;

      return p( x ) ;
   }
} ;

#endif
