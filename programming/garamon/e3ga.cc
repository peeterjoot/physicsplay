#include <e3ga/Mvec.hpp>
#include <iostream>
using namespace std;
using namespace e3ga;
using multivector = Mvec<double>;

int main()
{
   const multivector e1 = ::e1<double>();
   const multivector e2 = ::e2<double>();
//   const multivector e3 = e3<double>();

   // declaration / instantiation
   multivector mv1;            // empty multivector
   multivector mv2(mv1);       // initialization from another multivector
   multivector mv3 = mv1;      // initialization from another multivector


   // display
   cout << mv1 << endl;               // display a multivector
   cout << metric << endl;      // display the metric of e3ga
   cout << (mv1 ^ mv2) << endl;       // parenthesis needed (because of the priority of the operators)


   // ga constants
   I<double>();                 // pseudo-scalar of the algebra
   Iinv<double>();              // inverse pseudo-scalar of the algebra
   e12<double>();               // any multivector components 


   // initialisation and component access
   mv1 = 5*e1 -5*e2;  // initialization from constant multivectors
   mv1[E12] = 42.0;             // initialization per components
cout << mv1 << endl;
   mv2[E1] = mv1[E2];     // component access
   mv2[scalar] = 42.0;          // access to the scalar part of the multivector

   // basic usage
   multivector mv;             // empty multivector
   mv.roundZero(1.0e-8);              // inplace sets to 0 multivector's components with absolute value lower than a threshold
   mv.clear();                        // makes the multivector empty
   int k = 1;
   mv.clear(k);                       // remove the component of grade k
   if(mv.isEmpty()){}                 // test multivector emptiness
   if(mv1 == mv2){}                   // test multivector equality
   if(mv1 != mv2){}                   // test multivector difference


   // grade
   int a = mv.grade();                // highest grade of the multivector
   mv3 = mv1.grade(k);                // get the part of grade k of a multivector
   if(mv1.sameGrade(mv2)){}           // test if two multivectors have the same grade
   if(mv1.isGrade(k)){}               // test if a multivector contains components of grade k
   if(mv.isHomogeneous()){}           // check if the vector has a single grade
   mv.clear(k);                       // remove the component of grade k


   // norm
   double n1 = mv.norm();             // norm L2
   double n2 = mv.quadraticNorm();    // mv.norm() x mv.norm()


   // basic operators
   mv3 = mv1 + mv2 + 5.0;             // addition
   mv3 = mv1 - mv2 - 3.0;             // subtraction
   mv3 = -mv2;                        // unary minus
   mv3 = ~mv1;                        // reverse operator


   // products (operators)
   mv3 = mv1 ^ mv2;                   // outer product
   mv3 = mv1 | mv2;                   // inner product
   mv3 = mv1 < mv2;                   // left contraction
   mv3 = mv1 > mv2;                   // right contraction
   mv3 = mv1 * mv2;                   // geometric product
   mv3 = mv1 / mv2;                   // inverse operator (geometric product of mv1 and inv(mv2))


   // compact operators
   mv1 ^= mv2;                        // outer product
   mv1 |= mv2;                        // inner product
   mv1 *= mv2;                        // geometric product
   mv1 /= mv2;                        // inverse operator
   mv1 += mv2;                        // addition operator
   mv1 -= mv2;                        // subtraction operator


   // products (explicit)
   mv3 = mv1.scalarProduct(mv2);      // scalar product (sum of inner products between same-grade pairs from mv1 and mv2)
   mv3 = mv1.hestenesProduct(mv2);    // Hestenes product (inner product minus scalar product)
   mv3 = leftContraction(mv1,mv2);    // left contraction
   mv3 = rightContraction(mv1,mv2);   // right contraction
   mv3 = mv1.inv();                   // inverse function
   mv3 = mv.reverse();                // reverse function


   // dual
   mv3 = mv1.dual();                  // dual of the multivector
   mv3 = !mv1;                        // dual of the multivector


   // for high dimensions: useful fast dual-operation calls
   mv3 = mv1.outerPrimalDual(mv2);    // fast version of mv3 = mv1 ^ mv2.dual();
   mv3 = mv1.outerDualPrimal(mv2);    // fast version of mv3 = mv1.dual() ^ mv2;
   mv3 = mv1.outerDualDual(mv2);      // fast version of mv3 = mv1.dual() ^ mv2.dual();

   return 0;
}
