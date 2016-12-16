#include <boost/numeric/ublas/matrix.hpp>
#include <boost/numeric/ublas/operation.hpp>
#include <boost/numeric/ublas/io.hpp>
#include <complex>

//using namespace boost::numeric::ublas ;
namespace ublas = boost::numeric::ublas;
typedef std::complex<int> int_complex ;
typedef ublas::matrix<int_complex> cmatrix ;

void printit( const char * s, const cmatrix & m )
{
   using std::cout ;

   cout << "\\begin{align*}\n" << s << "\\begin{bmatrix}\n" ;

   for ( unsigned i = 0 ; i <= 3 ; i++ )
   {
      for ( unsigned j = 0 ; j <= 3 ; j++ )
      {
         int_complex a = m(i, j) ;

         if ( 0 == a.imag() )
         {
            cout << " " << a.real() << " " ;
         }
         else if ( 0 == a.real() )
         {
            if ( -1 == a.imag() )
            {
               cout << " -i " ;
            }
            else if ( 1 == a.imag() )
            {
               cout << " i " ;
            }
            else
            {
               cout << " " << a.imag() << " i " ;
            }
         }
         else
         {
            cout << " " << a.real() << " + " << a.imag() << " i " ;
         }

         if ( j != 3 )
         {
            cout << " & " ;
         }
      }

      cout << " \\\\\n" ;
   }

   cout << "\\end{bmatrix}\n\\end{align*}\n\n" ;
}

int main()
{

   int_complex i(0, 1) ;

   cmatrix gamma0(4, 4) ;
   cmatrix gamma1(4, 4) ;
   cmatrix gamma2(4, 4) ;
   cmatrix gamma3(4, 4) ;

   gamma0( 0, 0 ) = 1 ;
   gamma0( 1, 1 ) = 1 ;
   gamma0( 2, 2 ) = -1 ;
   gamma0( 3, 3 ) = -1 ;

   gamma1( 3, 0 ) = -1 ;
   gamma1( 2, 1 ) = -1 ;
   gamma1( 1, 2 ) = 1 ;
   gamma1( 0, 3 ) = 1 ;

   gamma2( 3, 0 ) = -i ;
   gamma2( 2, 1 ) = i ;
   gamma2( 1, 2 ) = i ;
   gamma2( 0, 3 ) = -i ;

   gamma3( 2, 0 ) = -1 ;
   gamma3( 3, 1 ) = 1 ;
   gamma3( 0, 2 ) = 1 ;
   gamma3( 1, 3 ) = -1 ;

   printit("\\gamma^1 = ", gamma0) ;
   printit("\\gamma^2 = ", gamma1) ;
   printit("\\gamma^3 = ", gamma2) ;
   printit("\\gamma^4 = ", gamma3) ;

// BEGIN:!perl generate_prods.pl > u

   {
      cmatrix t12(4,4) ;
      cmatrix g123(4,4) ;

      t12 = prod( gamma1, gamma2 ) ;
      g123 = prod( t12, gamma3 ) ;

      printit( "\\gamma^1 \\gamma^2 \\gamma^3 = ", g123 ) ;
   }


   {
      cmatrix t23(4,4) ;
      cmatrix g230(4,4) ;

      t23 = prod( gamma2, gamma3 ) ;
      g230 = prod( t23, gamma0 ) ;

      printit( "\\gamma^2 \\gamma^3 \\gamma^0 = ", g230 ) ;
   }


   {
      cmatrix t30(4,4) ;
      cmatrix g301(4,4) ;

      t30 = prod( gamma3, gamma0 ) ;
      g301 = prod( t30, gamma1 ) ;

      printit( "\\gamma^3 \\gamma^0 \\gamma^1 = ", g301 ) ;
   }


   cmatrix g00(4,4) ;
   g00 = prod( gamma0, gamma0 ) ;
   printit( "\\gamma^0 \\gamma^0 = ", g00 ) ;


   cmatrix g11(4,4) ;
   g11 = prod( gamma1, gamma1 ) ;
   printit( "\\gamma^1 \\gamma^1 = ", g11 ) ;


   cmatrix g22(4,4) ;
   g22 = prod( gamma2, gamma2 ) ;
   printit( "\\gamma^2 \\gamma^2 = ", g22 ) ;


   cmatrix g33(4,4) ;
   g33 = prod( gamma3, gamma3 ) ;
   printit( "\\gamma^3 \\gamma^3 = ", g33 ) ;




   {
      cmatrix t01(4,4) ;
      cmatrix g012(4,4) ;

      t01 = prod( gamma0, gamma1 ) ;
      g012 = prod( t01, gamma2 ) ;

      printit( "\\gamma^0 \\gamma^1 \\gamma^2 = ", g012 ) ;
   }


   cmatrix g01(4,4) ;
   g01 = prod( gamma0, gamma1 ) ;
   printit( "\\gamma^0 \\gamma^1 = ", g01 ) ;


   cmatrix g10(4,4) ;
   g10 = prod( gamma1, gamma0 ) ;
   printit( "\\gamma^1 \\gamma^0 = ", g10 ) ;


   cmatrix g02(4,4) ;
   g02 = prod( gamma0, gamma2 ) ;
   printit( "\\gamma^0 \\gamma^2 = ", g02 ) ;


   cmatrix g20(4,4) ;
   g20 = prod( gamma2, gamma0 ) ;
   printit( "\\gamma^2 \\gamma^0 = ", g20 ) ;


   cmatrix g03(4,4) ;
   g03 = prod( gamma0, gamma3 ) ;
   printit( "\\gamma^0 \\gamma^3 = ", g03 ) ;


   cmatrix g30(4,4) ;
   g30 = prod( gamma3, gamma0 ) ;
   printit( "\\gamma^3 \\gamma^0 = ", g30 ) ;


   cmatrix g12(4,4) ;
   g12 = prod( gamma1, gamma2 ) ;
   printit( "\\gamma^1 \\gamma^2 = ", g12 ) ;


   cmatrix g21(4,4) ;
   g21 = prod( gamma2, gamma1 ) ;
   printit( "\\gamma^2 \\gamma^1 = ", g21 ) ;


   cmatrix g13(4,4) ;
   g13 = prod( gamma1, gamma3 ) ;
   printit( "\\gamma^1 \\gamma^3 = ", g13 ) ;


   cmatrix g31(4,4) ;
   g31 = prod( gamma3, gamma1 ) ;
   printit( "\\gamma^3 \\gamma^1 = ", g31 ) ;


   cmatrix g23(4,4) ;
   g23 = prod( gamma2, gamma3 ) ;
   printit( "\\gamma^2 \\gamma^3 = ", g23 ) ;


   cmatrix g32(4,4) ;
   g32 = prod( gamma3, gamma2 ) ;
   printit( "\\gamma^3 \\gamma^2 = ", g32 ) ;


// END:!perl generate_prods.pl > u

   {
      cmatrix t12(4,4) ;
      cmatrix t123(4,4) ;
      cmatrix g0123(4,4) ;

      t12 = prod( gamma1, gamma2 ) ;
      t123 = prod( t12, gamma3 ) ;
      g0123 = prod( gamma0, t123 ) ;

      printit( "\\gamma^0 \\gamma^1 \\gamma^2 \\gamma^3 = ", g0123 ) ;
   }

   return 0 ;
}

