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

/// return a bitmask with a bit set for each unique basis element in the algebra.
int mv_bitmask( const mv & a )
{
   int m = 0 ;
   int k = 0 ;
   int b = 0 ;
   for ( int i = 0 ; i <= 3 ; i++ )
   {
      if ( a.gu() & (1 << i) )
      {
         for ( int j = 0 ; j < mv_gradeSize[i] ; j++ )
         {
            if ( a.m_c[k] )
            {
               m |= (1 << b) ;
            }

            k++ ;
            b++ ;
         }
      }
      else
      {
         b += mv_gradeSize[i] ;
      }
   }

   return m ;
}

class symbol ;
class sum ;
bool compareSymbol (const symbol & first, const symbol & second) ;
sum dot( const sum & a, const mv & b ) ;

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

   friend bool compareSymbol (const symbol & first, const symbol & second) ;
   friend sum dot( const sum & a, const mv & b ) ;

   void dump() const ;
} ;

void symbol::dump() const
{
   cout << symName
        << " ( "
        << toString(symNumeric)
        << " )" ;
   cout << endl ;
}

bool compareSymbol (const symbol & first, const symbol & second)
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
      int la = mv_bitmask( a )  ;
      int lb = mv_bitmask( b )  ;

      return la > lb ;
   }
}

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

   void normalize( const bool doPostSort = true )
   {
      listOfSymbols.sort( compareSymbol ) ;

      if ( doPostSort )
      {
         iter i = listOfSymbols.begin() ;

         while ( i != listOfSymbols.end() )
         {
            iter j = i ;
            symbolType & cur = (*i) ;

            j++ ;

            while ( j != listOfSymbols.end() )
            {
               const symbolType & next = (*j) ;

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

                     j = listOfSymbols.erase(j) ;
                  }
                  else if ( nmatch )
                  {
                     cur.symName = stringType("(") + cur.symName + stringType(" - ") + next.symName + stringType(")") ;

                     j = listOfSymbols.erase(j) ;
                  }
                  else
                  {
                     break ;
                  }
               }
               else
               {
                  break ;
               }
            }

            i = j ;
         }
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

   friend sum dot( const sum & a, const mv & b ) ;
} ;

sum dot( const sum & a, const mv & b )
{
   sum r ;

   sum::citer i = a.listOfSymbols.begin() ;

   while ( i != a.listOfSymbols.end() )
   {
      sum::symbolType t(*i) ;

      t.symNumeric = b << t.symNumeric ;

      r.listOfSymbols.push_front( t ) ;

      i++ ;
   }

   return r ;
}

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

#if 0
   symbol CosPsi("\\cos(\\psi/2)", 1) ;
   symbol IsinPsi("\\sin(\\psi/2)", -iZ) ;
   symbol CosTheta("\\cos(\\theta/2)", 1) ;
   symbol IsinTheta("\\sin(\\theta/2)", -iX) ;
   symbol CosPhi("\\cos(\\phi/2)", 1) ;
   symbol IsinPhi("\\sin(\\phi/2)", -iZ) ;
#else
   symbol CosPsi("C_\\psi", 1) ;
   symbol IsinPsi("S_\\psi", -iZ) ;
   symbol CosTheta("C_\\theta", 1) ;
   symbol IsinTheta("S_\\theta", -iX) ;
   symbol CosPhi("C_\\phi", 1) ;
   symbol IsinPhi("S_\\phi", -iZ) ;
#endif

   sum R_psi( CosPsi ) ; R_psi += IsinPsi ;
   sum R_theta( CosTheta ) ; R_theta += IsinTheta ;
   sum R_phi( CosPhi ) ; R_phi += IsinPhi ;

#if 1
   sum Rl = (R_phi * R_theta) * R_psi ;
#elif 1
   sum Rl = R_phi * R_theta ;
#else
   sum Rl = R_phi ;
#endif
   sum Rr = Rl.reverse() ;

#if 0
   cout << "expect identity:" << endl ;
   sum ident = Rl * Rr ;
   ident.dump() ;
//   cout << "normalized: expect identity:" << endl ;
//   ident.normalize( false ) ;
//   ident.dump() ;
   cout << "normalized: expect identity:" << endl ;
   ident.normalize( ) ;
   ident.dump() ;
#endif

   symbol se1("1", e1) ;
   symbol se2("1", e2) ;
   symbol se3("1", e3) ;

   {
//      cout << "R_{\\phi,z}(e_1):" << endl ;
      sum t(Rl) ;
      t *= se1 ;
      sum rot_e1 = t * Rr ;
      rot_e1.normalize() ;
//      rot_e1.dump() ;

      cout << "\n\n R_{11} &= \n\n" ;
      sum rot_e1_e1 = dot( rot_e1, e1 ) ;
      rot_e1_e1.normalize() ;
      rot_e1_e1.dump() ;

      cout << "\n\n R_{12} &= \n\n" ;
      sum rot_e1_e2 = dot( rot_e1, e2 ) ;
      rot_e1_e2.normalize() ;
      rot_e1_e2.dump() ;

      cout << "\n\n R_{13} &= \n\n" ;
      sum rot_e1_e3 = dot( rot_e1, e3 ) ;
      rot_e1_e3.normalize() ;
      rot_e1_e3.dump() ;
   }

   {
//      cout << "R_{\\phi,z}(e_2):" << endl ;
      sum t(Rl) ;
      t *= se2 ;
      sum rot_e2 = t * Rr ;
      rot_e2.normalize() ;
//      rot_e2.dump() ;

      cout << "\n\n R_{21} &= \n\n" ;
      sum rot_e2_e1 = dot( rot_e2, e1 ) ;
      rot_e2_e1.normalize() ;
      rot_e2_e1.dump() ;

      cout << "\n\n R_{22} &= \n\n" ;
      sum rot_e2_e2 = dot( rot_e2, e2 ) ;
      rot_e2_e2.normalize() ;
      rot_e2_e2.dump() ;

      cout << "\n\n R_{23} &= \n\n" ;
      sum rot_e2_e3 = dot( rot_e2, e3 ) ;
      rot_e2_e3.normalize() ;
      rot_e2_e3.dump() ;
   }

   {
//      cout << "R_{\\phi,z}(e_3):" << endl ;
      sum t(Rl) ;
      t *= se3 ;
      sum rot_e3 = t * Rr ;
      rot_e3.normalize() ;
//      rot_e3.dump() ;

      cout << "\n\n R_{31} &= \n\n" ;
      sum rot_e3_e1 = dot( rot_e3, e1 ) ;
      rot_e3_e1.normalize() ;
      rot_e3_e1.dump() ;

      cout << "\n\n R_{32} &= \n\n" ;
      sum rot_e3_e2 = dot( rot_e3, e2 ) ;
      rot_e3_e2.normalize() ;
      rot_e3_e2.dump() ;

      cout << "\n\n R_{33} &= \n\n" ;
      sum rot_e3_e3 = dot( rot_e3, e3 ) ;
      rot_e3_e3.normalize() ;
      rot_e3_e3.dump() ;
   }

   return 0 ;
}
