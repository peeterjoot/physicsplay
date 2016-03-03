/** \file springfunction.h
 */
#if !defined phy1610_springfunction_h_included
#define phy1610_springfunction_h_included

/**
   Model parameters for the kinetic energy of the spring.
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
      Kinetic energy of the spring function.

      E_s = a \left( \frac{b}{x} + \frac{d^2}{f (x - d)^2} - exp\left( -\frac{ c(x-b)^2 }{2 a} \right) \right)
    */
   double es( const double x ) const
   {
      double xdSq = ( x - d ) * ( x - d ) ;
      double xbSq = ( x - b ) * ( x - b ) ;
      return c1 / x + c2 / xdSq - a * std::exp( c3 * xbSq ) ;
   }

   /**
      Potential energy of the spring function.  E_w = - m g x
    */
   double ew( const double x ) const
   {
      return - g * m * x ;
   }

public:
   /**
      constructor.  set physical parameters for the kinetic energy function
    */
   gsl_spring_min_function( ) :
      a{1},
      b{0.1},
      c{100},
      d{0.5},
      f{2500},
      g{9.8},
      m{},
      c1{a * b},
      c2{a * d * d/f},
      c3{- c/(2 * a)}
   {
   }

   /**
      Pick a starting point for the interval that's a bit larger than the initiail singular point.
    */
   double start( ) const
   {
      return 0.0 + b/10 ;
   }

   /**
      Pick a starting point for the interval that's a bit smaller than the final singular point.
    */
   double end( ) const
   {
      return d - b/10 ;
   }

   /**
      Evaluate the energy of the spring at the specified point.
    */
   double operator() ( const double x ) const
   {
      return es( x ) + ew( x ) ;
   }

   /**
     reset the mass of the object to a new value
    */
   void setMass( const double mass )
   {
      m = mass ;
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
