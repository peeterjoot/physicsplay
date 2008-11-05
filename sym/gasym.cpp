#include <string>
#include <list>
#include <iostream>
#include <cstdio>

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

   void reverseMe()
   {
      symNumeric = reverse( symNumeric ) ;
   }

   friend bool compareSymbol (const symbol & first, const symbol & second)
   {
      const mv & a = first.symNumeric ;
      const mv & b = second.symNumeric ;

      if ( a.gu() > b.gu() )
      {
         return false ;
      }
      else if ( a.gu() < b.gu() )
      {
         return true ;
      }
      else
      {
         int k = 0 ;
         int ia = 0 ;

         for ( int i = 0 ; i <= 3 ; i++ )
         {
            if ( a.gu() & (1 << i) )
            {
               for ( int j = 0 ; j < mv_gradeSize[i] ; j++)
               {
					   float c1 = (float)mv_basisElementSignByIndex[ia] * a.m_c[k] ;
					   float c2 = (float)mv_basisElementSignByIndex[ia] * b.m_c[k] ;

                  if ( c1 > c2 )
                  {
                     return true ;
                  }
                  else if ( c1 )
                  {
                     return false ;
                  }

                  k++ ;
                  ia++ ;
               }
            }
			   else
            {
               ia += mv_gradeSize[i] ;
            }
         }

         return false ;
      }
   }
} ;

class sum
{
   typedef symbol symbolType ;
   typedef symbolType::stringType stringType ;
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

#if 0 // not used.
   void reverseMe()
   {
      iter i = listOfSymbols.begin() ;

      while ( i != listOfSymbols.end() )
      {
         (*i).reverseMe() ;

         i++ ;
      }
   }
#endif

   sum reverse() const
   {
      sum r(*this) ;
      iter i = r.listOfSymbols.begin() ;

      while ( i != r.listOfSymbols.end() )
      {
         (*i).reverseMe() ;

         i++ ;
      }

      return r ;
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

   void normalize()
   {
      listOfSymbols.sort( compareSymbol ) ;

      iter i = listOfSymbols.begin() ;

      while ( i != listOfSymbols.end() )
      {
         iter j = i ;
         symbolType & cur = (*i) ;

         j++ ;

         if ( j != listOfSymbols.end() )
         {
            const symbolType next = (*j) ;

            if ( cur.symNumeric.gu() && (cur.symNumeric.gu() == next.symNumeric.gu()) )
            {
               bool match = true ;
               bool nmatch = true ;
               int k = 0 ;
               int ia = 0 ;

               for ( int ii = 0 ; ii <= 3 ; ii++ )
               {
                  if ( cur.symNumeric.gu() & (1 << ii) )
                  {
                     for ( int jj = 0 ; jj < mv_gradeSize[ii] ; jj++)
                     {
                        if ( cur.symNumeric.m_c[k] != next.symNumeric.m_c[k] )
                        {
                           match = false ;
                        }

                        if ( cur.symNumeric.m_c[k] != -next.symNumeric.m_c[k] )
                        {
                           nmatch = false ;
                        }

                        k++ ;
                        ia++ ;
                     }
                  }
                  else
                  {
                     ia += mv_gradeSize[ii] ;
                  }
               }

               if ( match )
               {
                  cur.symName = stringType("(") + cur.symName + stringType(" + ") + next.symName + stringType(")") ;

                  listOfSymbols.erase(j) ;
               }
               else if ( nmatch )
               {
                  cur.symName = stringType("(") + cur.symName + stringType(" - ") + next.symName + stringType(")") ;

                  listOfSymbols.erase(j) ;
               }
            }
         }

         i++ ;
      }
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
   //e3ga::g2Profiling::init();

   bivector iZ = _bivector(e1 ^ e2) ;
   bivector iX = _bivector(e2 ^ e3) ;

   mv_string_wedge = " \\wedge " ;
   mv_string_mul = " " ;
   mv_string_fp = "%2.0f" ;
//   mv_string_start = "{" ;
//   mv_string_end = "}" ;
	mv_basisVectorNames[0] = "\\mathbf{e}_1" ;
	mv_basisVectorNames[1] = "\\mathbf{e}_2" ;
	mv_basisVectorNames[2] = "\\mathbf{e}_3" ;

   symbol CosPsi("\\cos(\\psi/2)", 1) ;
   symbol IsinPsi("\\sin(\\psi/2)", -iZ) ;

   sum R_psi( CosPsi ) ; R_psi += IsinPsi ;



   symbol CosTheta("\\cos(\\theta/2)", 1) ;
   symbol IsinTheta("\\sin(\\theta/2)", -iX) ;

   sum R_theta( CosTheta ) ; R_theta += IsinTheta ;



   symbol CosPhi("\\cos(\\phi/2)", 1) ;
   symbol IsinPhi("\\sin(\\phi/2)", -iZ) ;

   sum R_phi( CosPhi ) ; R_phi += IsinPhi ;

#if 0
   sum Rl = (R_psi * R_theta) * R_phi ;
#else
   sum Rl = R_phi ;
#endif
   sum Rr = Rl.reverse() ;

   cout << "expect identity:" << endl ;
   sum ident = Rl * Rr ;
   ident.normalize() ;
   ident.dump() ;

   symbol se1("1", e1) ;
   symbol se2("1", e2) ;
   symbol se3("1", e3) ;

   {
      cout << "R_{\\phi,z}(e_1):" << endl ;
      sum t(Rl) ;
      t *= se1 ;
      sum rot_e1 = t * Rr ;
      rot_e1.normalize() ;
      rot_e1.dump() ;
   }

   {
      cout << "R_{\\phi,z}(e_2):" << endl ;
      sum t(Rl) ;
      t *= se2 ;
      sum rot_e2 = t * Rr ;
      rot_e2.normalize() ;
      rot_e2.dump() ;
   }

   {
      cout << "R_{\\phi,z}(e_3):" << endl ;
      sum t(Rl) ;
      t *= se3 ;
      sum rot_e3 = t * Rr ;
      rot_e3.normalize() ;
      rot_e3.dump() ;
   }

   return 0 ;
}
