#include <string>
#include <list>
#include <iostream>

#include <libgasandbox/common.h>
#include <libgasandbox/e3ga.h>

using namespace e3ga ;
using namespace std ;

#if 0
float foopeekasm( const mv & v )
{
// 
// interesting.  looking at the generated asm shows that the compiler
// (g++ -O2) is
// able to inline this function despite the fact that the body of
// mv::gu() is not available until after it is used.
//
// Compilers are getting better!
// 
  return v.e3e1() ;
}
#endif

class symbol
{
   typedef std::string stringType ;
   stringType symName ;
   typedef mv valueType ;
   valueType symNumeric ;

   friend class sum ;

   void multiplyBySymbol( const stringType & v )
   {
      stringType s1("1") ;
      stringType s0("0") ;

      if ( v == s1 || symName == s0 )
      {
         // no-op
      }
      else if ( symName == s1 )
      {
         symName = v ;
      }
      else if ( v == s0 )
      {
         symName = s0 ;
      }
      else
      {
         symName += " " ;
         symName += v ;
      }
   }

public:
   symbol( const stringType & name, const valueType & value ) : symName(name), symNumeric(value)
   {
   }

   symbol & operator *= ( const valueType & scale )
   {
      symNumeric *= scale ;

      return *this ;
   }

   symbol & operator *= ( const stringType & scale )
   {
      multiplyBySymbol( scale ) ;

      return *this ;
   }

   symbol & operator *= ( const symbol & scale )
   {
      multiplyBySymbol( scale.symName ) ;

      symNumeric *= scale.symNumeric ;

      return *this ;
   }
} ;

class sum
{
   typedef symbol symbolType ;
   typedef std::list<symbolType> symbolsType ;
   typedef symbolsType::iterator iter ;
   typedef symbolsType::const_iterator citer ;
   symbolsType listOfSymbols ;

public:
   sum( ) {}

   sum( const symbolType & i )
   {
      listOfSymbols.push_front( i ) ;
   }

   sum & operator += ( const symbolType & more )
   {
      listOfSymbols.push_front( more ) ;

      return *this ;
   }

   sum & operator *= ( const symbolType & scale )
   {
      iter i = listOfSymbols.begin() ;

      while ( i != listOfSymbols.end() )
      {
         (*i) *= scale ;

         i++ ;
      }
   }

   friend sum operator * ( const sum & l, const sum & r )
   {
      sum agg ;
      citer i = l.listOfSymbols.begin() ;

      while ( i != l.listOfSymbols.end() )
      {
         citer j = r.listOfSymbols.begin() ;

         while ( j != r.listOfSymbols.end() )
         {
            symbolType tmp(*i) ;
            const symbolType & b = (*j) ;
            tmp *= b ;
            agg += tmp ;

            j++ ;
         }

         i++ ;
      }

      return agg ;
   }

   void dump(void) const
   {
      citer i = listOfSymbols.begin() ;
      bool first = true ;

      while ( i != listOfSymbols.end() )
      {
         if ( first )
         {
            cout << "\\left( " << endl ;
         }
         else
         {
            cout << "+ " ;
         }

         cout << (*i).symName
              << " ( "
              << toString((*i).symNumeric)
              << " )" ;
         cout << endl ;

         i++ ;
         first = false ;
      }

      cout << "\\right)" << endl ;
   }
} ;

int main(int argc, char*argv[])
{
   // profiling for Gaigen 2:
   e3ga::g2Profiling::init();

   bivector iZ = _bivector(e1 ^ e2) ;
   bivector iX = _bivector(e2 ^ e3) ;



   symbol CosPsi("\\cos(\\psi/2)", 1) ;
   symbol IsinPsi("\\sin(\\psi/2)", -iZ) ;

   sum R_psi( CosPsi ) ; R_psi += IsinPsi ;



   symbol CosTheta("\\cos(\\theta/2)", 1) ;
   symbol IsinTheta("\\sin(\\theta/2)", -iX) ;

   sum R_theta( CosTheta ) ; R_theta += IsinTheta ;



   symbol CosPhi("\\cos(\\phi/2)", 1) ;
   symbol IsinPhi("\\sin(\\phi/2)", -iZ) ;

   sum R_phi( CosPhi ) ; R_phi += IsinPhi ;


   sum R = (R_psi * R_theta) * R_phi ;

// no reverse implemented yet:

   symbol rCosPsi("\\cos(\\psi/2)", 1) ;
   symbol rIsinPsi("\\sin(\\psi/2)", iZ) ;

   sum rR_psi( rCosPsi ) ; rR_psi += rIsinPsi ;



   symbol rCosTheta("\\cos(\\theta/2)", 1) ;
   symbol rIsinTheta("\\sin(\\theta/2)", iX) ;

   sum rR_theta( rCosTheta ) ; rR_theta += rIsinTheta ;



   symbol rCosPhi("\\cos(\\phi/2)", 1) ;
   symbol rIsinPhi("\\sin(\\phi/2)", iZ) ;

   sum rR_phi( rCosPhi ) ; rR_phi += rIsinPhi ;

// okay rotors parts and reverses done.

#if 0
   sum Rl = (R_psi * R_theta) * R_phi ;
   sum Rr = (rR_phi * rR_theta) * rR_psi ;
#else
   sum Rl = R_phi ;
   sum Rr = rR_phi ;
#endif

   cout << "expect identity:" << endl ;
   sum ident = Rl * Rr ;
   ident.dump() ;

   symbol se1("1", e1) ;
   symbol se2("1", e2) ;
   symbol se3("1", e3) ;
   {
      cout << "R_{\\phi,z}(e_1):" << endl ;
      sum t(Rl) ;
      t *= se1 ;
      sum rot_e1 = t * Rr ;
      rot_e1.dump() ;
   }

   {
      cout << "R_{\\phi,z}(e_2):" << endl ;
      sum t(Rl) ;
      t *= se2 ;
      sum rot_e2 = t * Rr ;
      rot_e2.dump() ;
   }

   {
      cout << "R_{\\phi,z}(e_3):" << endl ;
      sum t(Rl) ;
      t *= se3 ;
      sum rot_e3 = t * Rr ;
      rot_e3.dump() ;
   }

   return 0;
}
