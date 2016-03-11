/*
 * Simple symbolic (multi)vector calculator.
 *
 * Peeter Joot (peeterjoot@protonmail.com).
 */


/*
 * TODO

 *) format the following as just the expression (ie: when the mv value == 1)

 ( C_\phi^2 - S_\phi^2 ) (  1 )

 *) implement factoring for toString.

 *) implement trig.

 */
#include <iostream>
#include <cstdio>

using namespace std ;

#include "sum.h"

bivector iZ = bivector(e1 ^ e2) ;
bivector iX = bivector(e2 ^ e3) ;

#if 0
//
// names too long.
//
symbol CosPsi("\\cos(\\psi/2)") ;
symbol IsinPsi("\\sin(\\psi/2)", -iZ) ;
symbol CosTheta("\\cos(\\theta/2)") ;
symbol IsinTheta("\\sin(\\theta/2)", -iX) ;
symbol CosPhi("\\cos(\\phi/2)") ;
symbol IsinPhi("\\sin(\\phi/2)", -iZ) ;
#else
symbol CosPsi("C_\\psi") ;
symbol IsinPsi("S_\\psi", -iZ) ;
symbol CosTheta("C_\\theta") ;
symbol IsinTheta("S_\\theta", -iX) ;
symbol CosPhi("C_\\phi") ;
symbol IsinPhi("S_\\phi", -iZ) ;
#endif

symbol se1(e1) ;
symbol se2(e2) ;
symbol se3(e3) ;

symbol x1("{x^1}", e1) ;
symbol x2("{x^2}", e2) ;
symbol x3("{x^3}", e2) ;

using std::string ;

void printIt( const std::string & label, sum & v )
{
   cout << "\\begin{align*}\n" << label ;
   v.dump( true ) ;
   cout << "\\end{align*}\n" ;
}

#if 0
void cayleyKlein()
{
#if 0
\begin{align*}
R &= a + b\Be_{21} + c \Be_{32} + d \Be_{31} \\
a &= \cos\left(\frac{\theta}{2}\right) \cos\left( \inv{2}\left(\psi+\phi\right) \right) \\
b &= \cos\left(\frac{\theta}{2}\right) \sin\left( \inv{2}\left(\psi+\phi\right) \right) \\
c &= \sin\left(\frac{\theta}{2}\right) \cos\left( \inv{2}\left(\psi-\phi\right) \right) \\
d &= \sin\left(\frac{\theta}{2}\right) \sin\left( \inv{2}\left(\psi-\phi\right) \right) \\
\end{align*}
#endif

   symbol a("a") ;
   symbol b("b", bivector(e2 ^ e1) ) ;
   symbol c("c", bivector(e3 ^ e2) ) ;
   symbol d("d", bivector(e3 ^ e1) ) ;

   sum Rl(a) ;
   Rl += b ;
   Rl += c ;
   Rl += d ;

   sum Rr = Rl.reverse() ;

#if 0
   cout << "R:" << endl ;
   Rl.dump( true ) ;
#endif

   sum t1(Rl) ;
   t1 *= se1 ;
   sum rot_e1 = t1 * Rr ;
   rot_e1.reduce() ;

   sum t2(Rl) ;
   t2 *= se2 ;
   sum rot_e2 = t2 * Rr ;
   rot_e2.reduce() ;

   sum t3(Rl) ;
   t3 *= se3 ;
   sum rot_e3 = t3 * Rr ;
   rot_e3.reduce() ;



   sum rot_e1_e1 = dot( rot_e1, e1 ) ;
   sum rot_e1_e2 = dot( rot_e1, e2 ) ;
   sum rot_e1_e3 = dot( rot_e1, e3 ) ;

   sum rot_e2_e1 = dot( rot_e2, e1 ) ;
   sum rot_e2_e2 = dot( rot_e2, e2 ) ;
   sum rot_e2_e3 = dot( rot_e2, e3 ) ;

   sum rot_e3_e1 = dot( rot_e3, e1 ) ;
   sum rot_e3_e2 = dot( rot_e3, e2 ) ;
   sum rot_e3_e3 = dot( rot_e3, e3 ) ;

   cout << "\\begin{align*}\n" ;
   cout << "\\begin{bmatrix}\n" ;

rot_e1_e1.dump(true) ; cout << "\n & " ;
rot_e2_e1.dump(true) ; cout << "\n & " ;
rot_e3_e1.dump(true) ; cout << "\n \\\\\n" ;

rot_e1_e2.dump(true) ; cout << "\n & " ;
rot_e2_e2.dump(true) ; cout << "\n & " ;
rot_e3_e2.dump(true) ; cout << "\n \\\\\n" ;

rot_e1_e3.dump(true) ; cout << "\n & " ;
rot_e2_e3.dump(true) ; cout << "\n & " ;
rot_e3_e3.dump(true) ; cout << "\n \\\\\n" ;

   cout << "\\end{bmatrix}\n" ;
   cout << "\\end{align*}\n" ;
}

void cayleyKlein2()
{
#if 0
\begin{align*}
R &= a - b\Be_{21} - c \Be_{32} - d \Be_{31} \\
a &= \cos\left(\frac{\theta}{2}\right) \cos\left( \inv{2}\left(\psi+\phi\right) \right) \\
b &= -\cos\left(\frac{\theta}{2}\right) \sin\left( \inv{2}\left(\psi+\phi\right) \right) \\
c &= -\sin\left(\frac{\theta}{2}\right) \cos\left( \inv{2}\left(\psi-\phi\right) \right) \\
d &= -\sin\left(\frac{\theta}{2}\right) \sin\left( \inv{2}\left(\psi-\phi\right) \right) \\
\end{align*}
#endif

   symbol a("a") ;
   symbol b("b", -bivector(e2 ^ e1) ) ;
   symbol c("c", -bivector(e3 ^ e2) ) ;
   symbol d("d", -bivector(e3 ^ e1) ) ;

   sum Rl(a) ;
   Rl += b ;
   Rl += c ;
   Rl += d ;

   sum Rr = Rl.reverse() ;

#if 0
   cout << "R:" << endl ;
   Rl.dump( true ) ;
#endif

   sum t1(Rl) ;
   t1 *= se1 ;
   sum rot_e1 = t1 * Rr ;
   rot_e1.reduce() ;

   sum t2(Rl) ;
   t2 *= se2 ;
   sum rot_e2 = t2 * Rr ;
   rot_e2.reduce() ;

   sum t3(Rl) ;
   t3 *= se3 ;
   sum rot_e3 = t3 * Rr ;
   rot_e3.reduce() ;



   sum rot_e1_e1 = dot( rot_e1, e1 ) ;
   sum rot_e1_e2 = dot( rot_e1, e2 ) ;
   sum rot_e1_e3 = dot( rot_e1, e3 ) ;

   sum rot_e2_e1 = dot( rot_e2, e1 ) ;
   sum rot_e2_e2 = dot( rot_e2, e2 ) ;
   sum rot_e2_e3 = dot( rot_e2, e3 ) ;

   sum rot_e3_e1 = dot( rot_e3, e1 ) ;
   sum rot_e3_e2 = dot( rot_e3, e2 ) ;
   sum rot_e3_e3 = dot( rot_e3, e3 ) ;

   cout << "\\begin{align*}\n" ;
   cout << "\\begin{bmatrix}\n" ;

rot_e1_e1.dump(true) ; cout << "\n & " ;
rot_e2_e1.dump(true) ; cout << "\n & " ;
rot_e3_e1.dump(true) ; cout << "\n \\\\\n" ;

rot_e1_e2.dump(true) ; cout << "\n & " ;
rot_e2_e2.dump(true) ; cout << "\n & " ;
rot_e3_e2.dump(true) ; cout << "\n \\\\\n" ;

rot_e1_e3.dump(true) ; cout << "\n & " ;
rot_e2_e3.dump(true) ; cout << "\n & " ;
rot_e3_e3.dump(true) ; cout << "\n \\\\\n" ;

   cout << "\\end{bmatrix}\n" ;
   cout << "\\end{align*}\n" ;
}

void cayleyKlein3()
{
#if 0
\begin{align*}
R &= a + b\Be_{21} - c \Be_{32} - d \Be_{31} \\
a &= \cos\left(\frac{\theta}{2}\right) \cos\left( \inv{2}\left(\psi+\phi\right) \right) \\
b &= \cos\left(\frac{\theta}{2}\right) \sin\left( \inv{2}\left(\psi+\phi\right) \right) \\
c &= -\sin\left(\frac{\theta}{2}\right) \cos\left( \inv{2}\left(\psi-\phi\right) \right) \\
d &= -\sin\left(\frac{\theta}{2}\right) \sin\left( \inv{2}\left(\psi-\phi\right) \right) \\
\end{align*}
#endif

   symbol a("a") ;
   symbol b("b", bivector(e2 ^ e1) ) ;
   symbol c("c", -bivector(e3 ^ e2) ) ;
   symbol d("d", -bivector(e3 ^ e1) ) ;

   sum Rl(a) ;
   Rl += b ;
   Rl += c ;
   Rl += d ;

   sum Rr = Rl.reverse() ;

#if 0
   cout << "R:" << endl ;
   Rl.dump( true ) ;
#endif

   sum t1(Rl) ;
   t1 *= se1 ;
   sum rot_e1 = t1 * Rr ;
   rot_e1.reduce() ;

   sum t2(Rl) ;
   t2 *= se2 ;
   sum rot_e2 = t2 * Rr ;
   rot_e2.reduce() ;

   sum t3(Rl) ;
   t3 *= se3 ;
   sum rot_e3 = t3 * Rr ;
   rot_e3.reduce() ;



   sum rot_e1_e1 = dot( rot_e1, e1 ) ;
   sum rot_e1_e2 = dot( rot_e1, e2 ) ;
   sum rot_e1_e3 = dot( rot_e1, e3 ) ;

   sum rot_e2_e1 = dot( rot_e2, e1 ) ;
   sum rot_e2_e2 = dot( rot_e2, e2 ) ;
   sum rot_e2_e3 = dot( rot_e2, e3 ) ;

   sum rot_e3_e1 = dot( rot_e3, e1 ) ;
   sum rot_e3_e2 = dot( rot_e3, e2 ) ;
   sum rot_e3_e3 = dot( rot_e3, e3 ) ;

   cout << "\\begin{align*}\n" ;
   cout << "\\begin{bmatrix}\n" ;

rot_e1_e1.dump(true) ; cout << "\n & " ;
rot_e2_e1.dump(true) ; cout << "\n & " ;
rot_e3_e1.dump(true) ; cout << "\n \\\\\n" ;

rot_e1_e2.dump(true) ; cout << "\n & " ;
rot_e2_e2.dump(true) ; cout << "\n & " ;
rot_e3_e2.dump(true) ; cout << "\n \\\\\n" ;

rot_e1_e3.dump(true) ; cout << "\n & " ;
rot_e2_e3.dump(true) ; cout << "\n & " ;
rot_e3_e3.dump(true) ; cout << "\n \\\\\n" ;

   cout << "\\end{bmatrix}\n" ;
   cout << "\\end{align*}\n" ;
}

void cayleyKlein4()
{
#if 0
\begin{align*}
R &= a - b\Be_{21} + c \Be_{32} - d \Be_{31} \\
a &= \cos\left(\frac{\theta}{2}\right) \cos\left( \inv{2}\left(\psi+\phi\right) \right) \\
b &= -\cos\left(\frac{\theta}{2}\right) \sin\left( \inv{2}\left(\psi+\phi\right) \right) \\
c &= \sin\left(\frac{\theta}{2}\right) \cos\left( \inv{2}\left(\psi-\phi\right) \right) \\
d &= -\sin\left(\frac{\theta}{2}\right) \sin\left( \inv{2}\left(\psi-\phi\right) \right) \\
\end{align*}
#endif

   symbol a("a") ;
   symbol b("b", -bivector(e2 ^ e1) ) ;
   symbol c("c", bivector(e3 ^ e2) ) ;
   symbol d("d", -bivector(e3 ^ e1) ) ;

   sum Rl(a) ;
   Rl += b ;
   Rl += c ;
   Rl += d ;

   sum Rr = Rl.reverse() ;

#if 0
   cout << "R:" << endl ;
   Rl.dump( true ) ;
#endif

   sum t1(Rl) ;
   t1 *= se1 ;
   sum rot_e1 = t1 * Rr ;
   rot_e1.reduce() ;

   sum t2(Rl) ;
   t2 *= se2 ;
   sum rot_e2 = t2 * Rr ;
   rot_e2.reduce() ;

   sum t3(Rl) ;
   t3 *= se3 ;
   sum rot_e3 = t3 * Rr ;
   rot_e3.reduce() ;



   sum rot_e1_e1 = dot( rot_e1, e1 ) ;
   sum rot_e1_e2 = dot( rot_e1, e2 ) ;
   sum rot_e1_e3 = dot( rot_e1, e3 ) ;

   sum rot_e2_e1 = dot( rot_e2, e1 ) ;
   sum rot_e2_e2 = dot( rot_e2, e2 ) ;
   sum rot_e2_e3 = dot( rot_e2, e3 ) ;

   sum rot_e3_e1 = dot( rot_e3, e1 ) ;
   sum rot_e3_e2 = dot( rot_e3, e2 ) ;
   sum rot_e3_e3 = dot( rot_e3, e3 ) ;

   cout << "\\begin{align*}\n" ;
   cout << "\\begin{bmatrix}\n" ;

rot_e1_e1.dump(true) ; cout << "\n & " ;
rot_e2_e1.dump(true) ; cout << "\n & " ;
rot_e3_e1.dump(true) ; cout << "\n \\\\\n" ;

rot_e1_e2.dump(true) ; cout << "\n & " ;
rot_e2_e2.dump(true) ; cout << "\n & " ;
rot_e3_e2.dump(true) ; cout << "\n \\\\\n" ;

rot_e1_e3.dump(true) ; cout << "\n & " ;
rot_e2_e3.dump(true) ; cout << "\n & " ;
rot_e3_e3.dump(true) ; cout << "\n \\\\\n" ;

   cout << "\\end{bmatrix}\n" ;
   cout << "\\end{align*}\n" ;
}

void cayleyKlein5()
{
#if 0
\begin{align*}
R &= a - b\Be_{21} - c \Be_{32} + d \Be_{31} \\
a &= \cos\left(\frac{\theta}{2}\right) \cos\left( \inv{2}\left(\psi+\phi\right) \right) \\
b &= -\cos\left(\frac{\theta}{2}\right) \sin\left( \inv{2}\left(\psi+\phi\right) \right) \\
c &= -\sin\left(\frac{\theta}{2}\right) \cos\left( \inv{2}\left(\psi-\phi\right) \right) \\
d &= \sin\left(\frac{\theta}{2}\right) \sin\left( \inv{2}\left(\psi-\phi\right) \right) \\
\end{align*}
#endif

   symbol a("a") ;
   symbol b("b", -bivector(e2 ^ e1) ) ;
   symbol c("c", -bivector(e3 ^ e2) ) ;
   symbol d("d", bivector(e3 ^ e1) ) ;

   sum Rl(a) ;
   Rl += b ;
   Rl += c ;
   Rl += d ;

   sum Rr = Rl.reverse() ;

#if 0
   cout << "R:" << endl ;
   Rl.dump( true ) ;
#endif

   sum t1(Rl) ;
   t1 *= se1 ;
   sum rot_e1 = t1 * Rr ;
   rot_e1.reduce() ;

   sum t2(Rl) ;
   t2 *= se2 ;
   sum rot_e2 = t2 * Rr ;
   rot_e2.reduce() ;

   sum t3(Rl) ;
   t3 *= se3 ;
   sum rot_e3 = t3 * Rr ;
   rot_e3.reduce() ;



   sum rot_e1_e1 = dot( rot_e1, e1 ) ;
   sum rot_e1_e2 = dot( rot_e1, e2 ) ;
   sum rot_e1_e3 = dot( rot_e1, e3 ) ;

   sum rot_e2_e1 = dot( rot_e2, e1 ) ;
   sum rot_e2_e2 = dot( rot_e2, e2 ) ;
   sum rot_e2_e3 = dot( rot_e2, e3 ) ;

   sum rot_e3_e1 = dot( rot_e3, e1 ) ;
   sum rot_e3_e2 = dot( rot_e3, e2 ) ;
   sum rot_e3_e3 = dot( rot_e3, e3 ) ;

   cout << "\\begin{align*}\n" ;
   cout << "\\begin{bmatrix}\n" ;

rot_e1_e1.dump(true) ; cout << "\n & " ;
rot_e2_e1.dump(true) ; cout << "\n & " ;
rot_e3_e1.dump(true) ; cout << "\n \\\\\n" ;

rot_e1_e2.dump(true) ; cout << "\n & " ;
rot_e2_e2.dump(true) ; cout << "\n & " ;
rot_e3_e2.dump(true) ; cout << "\n \\\\\n" ;

rot_e1_e3.dump(true) ; cout << "\n & " ;
rot_e2_e3.dump(true) ; cout << "\n & " ;
rot_e3_e3.dump(true) ; cout << "\n \\\\\n" ;

   cout << "\\end{bmatrix}\n" ;
   cout << "\\end{align*}\n" ;
}

void euler()
{
   sum R_psi( CosPsi ) ; R_psi += IsinPsi ;
   sum R_theta( CosTheta ) ; R_theta += IsinTheta ;
   sum R_phi( CosPhi ) ; R_phi += IsinPhi ;

#if 1
   sum Rl = (R_phi * R_theta) * R_psi ;
#elif 0
   sum Rl = R_phi * R_theta ;
#else
   sum Rl = R_phi ;
#endif
   sum Rr = Rl.reverse() ;

#if 1
   cout << "R:" << endl ;
   Rl.dump( true ) ;
#endif

// compute the rotation in coordinates.
#if 0
   symbol x1("{x^1}", e1) ;
   symbol x2("{x^2}", e2) ;
   symbol x3("{x^3}", e2) ;

   sum x(x1) ; x += x2 ; x += x3 ;

   sum y = ( Rl * x ) * Rr ;
   y.dump( true ) ;

   cout << "In coordinates: " << endl ;
   sum y_e1 = dot( y, e1 ) ;
   sum y_e2 = dot( y, e2 ) ;
   sum y_e3 = dot( y, e3 ) ;

   y_e1.dump( true ) ;
   y_e2.dump( true ) ;
   y_e3.dump( true ) ;
#endif

// output more readable to do this in pieces:
#if 0
   cout << "\\begin{align*}\n" ;

   {
      sum t(Rl) ;
      t *= se1 ;
      sum rot_e1 = t * Rr ;
      rot_e1.reduce() ;

      cout << "R_{11} &=\n" ;
      sum rot_e1_e1 = dot( rot_e1, e1 ) ;
      rot_e1_e1.dump( true ) ;

      cout << " \\\\\nR_{21} &=\n" ;
      sum rot_e1_e2 = dot( rot_e1, e2 ) ;
      rot_e1_e2.dump( true ) ;

      cout << " \\\\\nR_{31} &=\n" ;
      sum rot_e1_e3 = dot( rot_e1, e3 ) ;
      rot_e1_e3.dump( true ) ;
   }

   {
      sum t(Rl) ;
      t *= se2 ;
      sum rot_e2 = t * Rr ;
      rot_e2.reduce() ;

      cout << " \\\\\nR_{12} &=\n" ;
      sum rot_e2_e1 = dot( rot_e2, e1 ) ;
      rot_e2_e1.dump( true ) ;

      cout << " \\\\\nR_{22} &=\n" ;
      sum rot_e2_e2 = dot( rot_e2, e2 ) ;
      rot_e2_e2.dump( true ) ;

      cout << " \\\\\nR_{32} &=\n" ;
      sum rot_e2_e3 = dot( rot_e2, e3 ) ;
      rot_e2_e3.dump( true ) ;
   }

   {
      sum t(Rl) ;
      t *= se3 ;
      sum rot_e3 = t * Rr ;
      rot_e3.reduce() ;

      cout << " \\\\\nR_{13} &=\n" ;
      sum rot_e3_e1 = dot( rot_e3, e1 ) ;
      rot_e3_e1.dump( true ) ;

      cout << " \\\\\nR_{23} &=\n" ;
      sum rot_e3_e2 = dot( rot_e3, e2 ) ;
      rot_e3_e2.dump( true ) ;

      cout << " \\\\\nR_{33} &=\n" ;
      sum rot_e3_e3 = dot( rot_e3, e3 ) ;
      rot_e3_e3.dump( true ) ;
   }

   cout << "\\end{align*}\n" ;
#endif
}

void euler2()
{
   // aim of this is to verify that this:
#if 0
C_\theta
\exp\left(
\frac{- \Be_{12} }{2}\left(\psi+\phi\right)
\right)
%\\
%&
+
S_\theta
\exp\left(
\frac{\Be_{12} }{2}\left(\psi-\phi\right)
\right)
\Be_{32} \\

  // which produces this:
( - C_\theta S_\phi S_\psi + C_\phi C_\psi C_\theta ) (  1 )
+ ( - C_\psi S_\phi S_\theta + C_\phi S_\psi S_\theta ) (  -  1 \Be_1 \wedge \Be_3 )
+ ( - S_\phi S_\psi S_\theta - C_\phi C_\psi S_\theta ) (  1 \Be_2 \wedge \Be_3 )
+ ( - C_\psi C_\theta S_\phi - C_\phi C_\theta S_\psi ) (  1 \Be_1 \wedge \Be_2 )

// does in fact match
// Rl.dump() from euler() above (it does.)

#endif

   sum R_psi( CosPsi ) ; R_psi += IsinPsi ;
   sum R_phi( CosPhi ) ; R_phi += IsinPhi ;

   symbol SinTheta("S_\\theta") ;
// cosine theta part
   sum R_c = sum( CosTheta ) * (R_psi * R_phi) ;
// sine theta part
   sum R_s = sum( SinTheta ) * (sum(R_psi).reverse() * R_phi ) ;

   bivector e32 = bivector(e3 ^ e2) ;
   R_s *= symbol( e32 ) ;

   sum R(R_c) ; R += R_s ;

   R.dump( true ) ;
}

void rotation()
{
   symbol Z(term(1), mv(iZ) ) ;
   symbol Zbar(Z) ;
   Zbar.reverseMe() ;

   sum x(x1) ; x += x2 ; x += x3 ;

   sum y = ( Z * x ) * Zbar ;
   y.dump( true ) ;

   cout << "In coordinates: " << endl ;
   sum y_e1 = dot( y, e1 ) ;
   sum y_e2 = dot( y, e2 ) ;
   sum y_e3 = dot( y, e3 ) ;

   y_e1.dump( true ) ;
   y_e2.dump( true ) ;
   y_e3.dump( true ) ;
}


void sphericalPolar()
{
   // full angle sign and cosine shorthand:
   term rx("C_\\phi") ; rx *= term("C_\\theta") ;
   term ry("C_\\phi") ; ry *= term("S_\\theta") ;
   term rz("S_\\phi") ;

   sum rcap( symbol(rx, e1) ) ;
   rcap += symbol(ry, e2) ;
   rcap += symbol(rz, e3) ;

   bivector i = bivector(e1 ^ e2) ;

//C^2 - S^2 = 1/4( e^2ix + e^-2ix + 2 + e^2ix + e^-2ix - 2 )  = cos(2x)

#if 0
   // end up with a mess of half angles.  Hardcode.
   sum Rth( symbol( "{\\cos(theta/2)}") ) ;
   Rth += symbol( "{\\sin(theta/2)}", i ) ;

   sum u = (Rth * symbol(e1)) * Rth.reverse() ;
#else
   sum u( symbol( "C_\\theta", e1 )) ; u += symbol( "S_\\theta", e2 ) ;
#endif
   //printIt( "u = ", u ) ;

   sum thetacap(u) ; thetacap *= symbol( i ) ;
//   printIt( "thetacap=", thetacap ) ;

   mv Imv( mv(i) ^ e3 ) ;
   sum I( Imv ) ;
//   printIt( "I=", I ) ;

   sum phicap(-Imv) ;
   sum rthetaplane(rcap ^ thetacap) ;
   printIt( "\\rcap \\wedge \\thetacap &= ", rthetaplane ) ;
   phicap *= rthetaplane ;

   printIt( "thetacap = ", thetacap ) ;
   printIt( "rcap = ", rcap ) ;
   printIt( "phicap=", phicap ) ;

   sum phicap2( symbol( "C_\\phi", e3 )) ;
   {
   term Sphi = term("S_\\phi") ;
   symbol t1( "S_\\theta", -e2 ) ;
   t1 *= Sphi ;

   symbol t2( "C_\\theta", -e1 ) ;
   t2 *= Sphi ;

   phicap2 += t1 ;
   phicap2 += t2 ;
   }

   // manually reduce:
   phicap = phicap2 ;

// test case.  Should be zero:
#if 0
   sum r_dot_theta(rcap) ; r_dot_theta <<= thetacap ;
   sum r_dot_phi(rcap) ; r_dot_phi <<= phicap ;
   sum theta_dot_phi(thetacap) ; theta_dot_phi <<= phicap ;

   printIt("rcap \\cdot thetacap=", r_dot_theta) ;
   printIt("rcap \\cdot phicap=", r_dot_phi) ;
   printIt("thetacap \\cdot phicap=", theta_dot_phi) ;
#endif

// test case.  Should be one:
#if 0

// manually reduce for verification: ... this too-dumb calculator doesn't know trig!
//( C_\phi S_\theta^2 + C_\phi C_\theta^2 ) (  1 \Be_3 ) == C_\phi e3
//+ - S_\phi S_\theta (  1 \Be_2 )
//+ - C_\theta S_\phi (  1 \Be_1 )

   sum phicap_sq(phicap2) ; phicap_sq *= phicap2 ;

   printIt( "\\phicap^2 = ", phicap_sq ) ;

   sum rcap_sq(rcap) ; rcap_sq *= rcap ;

   printIt( "\\rcap^2 = ", rcap_sq ) ;

   sum thetacap_sq(thetacap) ; thetacap_sq *= thetacap ;

   printIt( "\\thetacap^2 = ", thetacap_sq ) ;
#endif
}

void sphericalPolar2()
{
   // half angles.
   term Ct("C_\\theta") ;
   term St("S_\\theta") ;
   term Cp("C_\\phi") ; 
   term Sp("S_\\phi") ;

   symbol scalarRtheta( Ct, 1 ) ;
   symbol bivectorRtheta( St, bivector( e1 ^ e2 ) ) ;

   symbol scalarRphi( Cp, 1 ) ;
   symbol bivectorRphi( Sp, bivector( e1 ^ e3 ) ) ;

   sum Rtheta(scalarRtheta) ; Rtheta += bivectorRtheta ;
   sum Rphi(scalarRphi) ; Rphi += bivectorRphi ;

   sum R(Rphi) ; //R *= Rtheta ;
   sum rR = R.reverse() ;

   sum rcap(rR)      ; rcap      *= symbol( e1 ) ; rcap     *= R ;
   sum thetacap(rR)  ; thetacap  *= symbol( e2 ) ; thetacap *= R ;
   sum phicap(rR)    ; phicap    *= symbol( e3 ) ; phicap   *= R ;

   printIt( "\\rcap &=", rcap ) ;
   printIt( "\\thetacap &=", thetacap ) ;
   printIt( "\\phicap &=", phicap ) ;
}

void baylisEuler()
{
   term Ct("C_\\theta") ;
   term St("S_\\theta") ;
   term Cp("C_\\phi") ; 
   term Sp("S_\\phi") ;
   term Cc("C_\\chi") ; 
   term Sc("S_\\chi") ;
   term h("\\inv{2}") ;

   sum p3( 1 ) ;
   p3 += symbol( e3 ) ;
   p3 *= symbol( h, mv(1) ) ;

   symbol scalarRphi( Cp, 1 ) ;
   symbol bivectorRphi( Sp, bivector( e2 ^ e1 ) ) ;

   symbol scalarRtheta( Ct, 1 ) ;
   symbol bivectorRtheta( St, bivector( e1 ^ e3 ) ) ;

   symbol scalarRchi( Cc, 1 ) ;
   symbol bivectorRchi( Sc, bivector( e2 ^ e1 ) ) ;

   sum Rtheta(scalarRtheta) ; Rtheta += bivectorRtheta ;
   sum Rphi(scalarRphi) ; Rphi += bivectorRphi ;
   sum Rchi(scalarRchi) ; Rchi += bivectorRchi ;

   printIt( "Rtheta:", Rtheta ) ;
   printIt( "Rphi:", Rphi ) ;
   printIt( "Rchi:", Rchi ) ;
   printIt( "p3:", p3 ) ;

   sum prod(Rphi) ;
   prod *= Rtheta ;
   prod *= Rchi ;
   prod *= p3 ;

   printIt( "prod:", prod ) ;
}
#endif

#if 0
   A &=
   Be_1 e^{i phi} e^{j theta} 
   Be_2 e^{i phi} sin(theta)

   j = e_3 wedge e_1 e^{i phi}
   i = e_1 wedge e_2
#endif
/**
   build up the matrix

   \param thetaStr [in]
      Example: "theta"
   \param phiStr [in]
      Example: "phi"
   \param A1 [out]
       first row.
   \param A2 [out]
       second row.
 */
void sphericalPendulum( 
   const std::string & cosPrefix,
   const std::string & sinePrefix,
   const std::string & trigSuffix,
   const std::string & thetaStr,
   const std::string & phiStr,
   sum & A1,
   sum & A2 )
{
   term cos_theta( cosPrefix + thetaStr + trigSuffix ) ;
   term sin_theta( sinePrefix + thetaStr + trigSuffix ) ;
   term cos_phi( cosPrefix + phiStr + trigSuffix ) ; 
   term sin_phi( sinePrefix + phiStr + trigSuffix ) ;

   symbol scalarExpIphi( cos_phi, 1 ) ;
   symbol bivectorExpIphi( sin_phi, bivector( e1 ^ e2 ) ) ;
   sum ExpIphi(scalarExpIphi) ; ExpIphi += bivectorExpIphi ;
   //printIt( std::string("e^{i") + phiStr + std::string("} &="), ExpIphi ) ;

   sum jBivector( symbol( mv( e3 ^ e1) ) ) ;
   jBivector *= ExpIphi ;
   //printIt( "j &=", jBivector ) ;

   sum ExpJtheta( symbol( sin_theta, 1 ) ) ;
   ExpJtheta *= jBivector ;
   ExpJtheta += symbol( cos_theta, 1 ) ;
   //printIt( std::string("e^{j") + thetaStr + std::string("} &="), ExpJtheta ) ;

   A1 = symbol( e1 ) ;
//   printIt( "A1 = ", A1 ) ;
   A1 *= ExpIphi ;
//   printIt( "A1 = ", A1 ) ;
   A1 *= ExpJtheta ;
//   printIt( "A1 = ", A1 ) ;

   A2 = symbol( e2 ) ;
//   printIt( "A2 = ", A2 ) ;
   A2 *= ExpIphi ;
//   printIt( "A2 = ", A2 ) ;
   A2 *= symbol( sin_theta, 1 ) ;
//   printIt( "A2 = ", A2 ) ;

}

// HACK: switch to setStringFormat when gaigen2.5.1 generator bug is fixed.
namespace e3ga
{
   void e3ga_setStringFormat(const char *what, const char *format);
} ;

void someSortOfSphericalPendulumStuff()
{
   sum A1, A2 ;
   sum B1, B2 ;
#if 0
   sphericalPendulum( "C_", "S_", "", "{\\theta_r}", "{\\phi_r}", A1, A2 ) ;
   sphericalPendulum( "C_", "S_", "", "{\\theta_c}", "{\\phi_c}", B1, B2 ) ;
#elif 0
   sphericalPendulum( "cos(", "sin(", ")", "theta", "phi", A1, A2 ) ;
   sphericalPendulum( "cos(", "sin(", ")", "alpha", "beta", B1, B2 ) ;
#else
   sphericalPendulum( "Cos[", "Sin[", "]", "theta", "phi", A1, A2 ) ;
   sphericalPendulum( "Cos[", "Sin[", "]", "alpha", "beta", B1, B2 ) ;
#endif

   sum AB11 = A1 ;
   AB11 *= B1 ;   
   printIt( "AB11 : Simplify[] ", AB11 ) ;

   sum AB12 = A1 ;
   AB12 *= B2 ;   
   printIt( "AB12 : Simplify[]", AB12 ) ;

   sum AB21 = A2 ;
   AB21 *= B1 ;   
   printIt( "AB21 : Simplify[]", AB21 ) ;

   sum AB22 = A2 ;
   AB22 *= B2 ;   
   printIt( "AB22 : Simplify[]", AB22 ) ;
}

void rotationQmTwoPs7q3()
{
   symbol y1("x", e1) ;
   symbol y2("y", e2) ;
   symbol y3("z", e2) ;

   symbol CosMu("C_{\\mu/2}") ;
   symbol SinMu("S_{\\mu/2}") ;
   symbol ncap ( "\\inv{\\sqrt{2}}", mv( e3 ^ (e1 - e2)) ) ;

   symbol sinPart(ncap) ;
   sinPart *= SinMu ;

   sum expMu(CosMu) ;
   expMu += sinPart ;

   sum RexpMu = expMu.reverse() ;

   sum x(y1) ; x += y2 ; x += y3 ;
   sum y(RexpMu) ;
   y *= x ;
   y *= expMu ;
   y.dump( true ) ;

   cout << "In coordinates: " << endl ;
   sum y_e1 = dot( y, e1 ) ;
   sum y_e2 = dot( y, e2 ) ;
   sum y_e3 = dot( y, e3 ) ;

   y_e1.dump( true ) ;
   y_e2.dump( true ) ;
   y_e3.dump( true ) ;
}

int main(int argc, char*argv[])
{
   e3ga_setStringFormat( "wedge", "\\wedge " ) ;
   e3ga_setStringFormat( "mul", " " ) ;
   e3ga_setStringFormat( "fp", "%2.0f" ) ;

   e3ga_basisVectorNames[0] = "\\Be_1" ;
   e3ga_basisVectorNames[1] = "\\Be_2" ;
   e3ga_basisVectorNames[2] = "\\Be_3" ;

//   euler() ;
//   rotation() ;
//   euler2() ;
//   cayleyKlein() ;
//   cayleyKlein2() ;
//   cayleyKlein3() ;
//   cayleyKlein4() ;
//   cayleyKlein5() ;
//   sphericalPolar() ;
//   sphericalPolar2() ;
//   baylisEuler() ;

   rotationQmTwoPs7q3() ;

   return 0 ;
}
