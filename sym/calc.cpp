/*
 * Simple symbolic calculator.
 *
 * Peeter Joot (peeterjoot@protonmail.com).
 *
 */

#include <iostream>

using namespace std ;

#include "expression.h"

// calculate coeff's of (1 + x^2)/(1 + x^4) = A/() + B/() + C/() + D/()
void tc1(void)
{
   expression ri( term("\\sqrt{i}") ) ;
   expression x( term("x") ) ;
   expression i( term("i") ) ;
   expression iri( term("i") ) ; iri *= ri ;
   expression A( term("A") ) ;
   expression B( term("B") ) ;
   expression C( term("C") ) ;
   expression D( term("D") ) ;

   expression q1(x) ;
   q1 -= ri ;
   q1 *= A ;
//   q1.reduce() ;
//   cout << q1.toString() ;

   {
      expression q2(x) ;
      q2 += ri ;
      q2 *= B ;
//   q2.reduce() ;
//   cout << q2.toString() ;

      q1 += q2 ;
   }

   expression f1(x) ;
   f1 *= x ;
   f1 += i ;
   f1 *= q1 ;
   f1.reduce() ;
//   cout << f1.toString() ;

//   q1.reduce() ;
//   cout << q1.toString() ;

   expression q3(x) ; q3 -= iri ; q3 *= C ;
   {
      expression q4(x) ; q4 += iri ; q4 *= D ;

      q3 += q4 ;
//   q3.reduce() ;
//   cout << q3.toString() ;
   }

   {
      expression f2(x) ;
      f2 *= x ;
      f2 -= i ;
//   f2.reduce() ;
//   cout << f2.toString() ;
      f2 *= q3 ;

      f1 += f2 ;
   }

 f1.reduce() ;
   cout << f1.toString() ;
}

int main(int argc, char*argv[])
{
   tc1() ;

   return 0 ;
}
