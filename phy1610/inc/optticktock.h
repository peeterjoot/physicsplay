/** \file optticktock.h
 */
#if !defined phy1610_optticktock_h_included
#define phy1610_optticktock_h_included

#if defined USE_TICK_TOCK
   #include "ticktock.h"
#endif

/**
   tick tock code or no-op, depending on whether USE_TICK_TOCK is defined.
 */
class TickTockOrNoOp 
#if defined USE_TICK_TOCK
   : private TickTock
#endif
{
public:
#if defined USE_TICK_TOCK
   using TickTock::tick ;
   using TickTock::silent_tock ;
#else
   void tick() {}              
   double silent_tock() const { return 0.0 ; }
#endif
} ;

#endif
