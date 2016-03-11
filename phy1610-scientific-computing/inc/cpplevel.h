/**
   \file cpplevel.h

   Some macros to test for c++ release levels.
 */
#if !defined phy1610_cpplevel_h_included
#define phy1610_cpplevel_h_included

#if defined __cplusplus && (__cplusplus >= 201103L)
   #define HAVE_CPLUSPLUS_11
#endif

#if defined __cplusplus && (__cplusplus >= 201402L)
   #define HAVE_CPLUSPLUS_14
#endif

#endif
