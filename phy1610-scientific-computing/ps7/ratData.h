/** \file ratData.h
 */
#if !defined phy1610_ratData_h_included
#define phy1610_ratData_h_included

#include "rarray"
#include <complex>

using carray = rarray<std::complex<double>, 1> ;
using darray = rarray<double, 1> ;

struct ratData
{
   darray   m_times ;
   carray   m_signal ;

   void open( const std::string ratPath, const std::string filename ) ;

   void writeToCsv( const std::string outFileName ) const ;
} ;

#endif
