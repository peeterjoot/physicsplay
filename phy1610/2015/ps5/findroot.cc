#include <stdio.h>
#include <gsl/gsl_errno.h>
#include <gsl/gsl_math.h>
#include <gsl/gsl_roots.h>

struct quadratic_params
{
    double a, b, c ;
} ;

double quadratic( double x, void * params ) ;
double quadratic_deriv( double x, void * params ) ;
void quadratic_fdf( double x, void * params, double *y, double *dy ) ;

double quadratic( double x, void * params )
{
   struct quadratic_params *p = (struct quadratic_params *) params ;
   double a = p->a ;
   double b = p->b ;
   double c = p->c ;
   return (a * x + b) * x + c ;
}

double quadratic_deriv( double x, void * params )
{
   struct quadratic_params *p = (struct quadratic_params *) params ;
   double a = p->a ;
   double b = p->b ;
   return 2.0 * a * x + b ;
}

void quadratic_fdf( double x, void * params, double *y, double *dy )
{
   struct quadratic_params *p = (struct quadratic_params *) params ;
   double a = p->a ;
   double b = p->b ;
   double c = p->c ;
   *y = (a * x + b) * x + c ;
   *dy = 2.0 * a * x + b ;
}

int main(void)
{
   int status ;
   int iter = 0, max_iter = 100 ;
   const gsl_root_fsolver_type *T ;
   gsl_root_fsolver *s ;
   double r = 0, r_expected = sqrt (5.0) ;
   double x_lo = 0.0, x_hi = 5.0 ;
   gsl_function F ;
   struct quadratic_params params = { 1.0, 0.0, -5.0 } ;
   F.function = &quadratic ;

   F.params = &params ;
   T = gsl_root_fsolver_brent ;
   s = gsl_root_fsolver_alloc( T ) ;

   gsl_root_fsolver_set( s, &F, x_lo, x_hi ) ;

   printf( "using %s method\n", gsl_root_fsolver_name (s)) ;
   printf( "%5s [%9s, %9s] %9s %10s %9s\n",
           "iter", "lower", "upper", "root", "err", "err(est)") ;

   do {
      iter++ ;
      status = gsl_root_fsolver_iterate (s) ;
      r = gsl_root_fsolver_root (s) ;
      x_lo = gsl_root_fsolver_x_lower (s) ;
      x_hi = gsl_root_fsolver_x_upper (s) ;
      status = gsl_root_test_interval (x_lo, x_hi, 0, 0.001) ;
      if ( status == GSL_SUCCESS )
      {
          printf ("Converged:\n") ;
      }

      printf( "%5d [%.7f, %.7f] %.7f %+.7f %.7f\n",
              iter, x_lo, x_hi, r, r - r_expected, x_hi - x_lo ) ;

   } while (status == GSL_CONTINUE && iter < max_iter) ;

   gsl_root_fsolver_free (s) ;

   return status ;
}
