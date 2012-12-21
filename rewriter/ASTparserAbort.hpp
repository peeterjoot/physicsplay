static inline unsigned int ecfGetComponentIndex( unsigned int id ) { return ( ( id & 255 ) >> 19 ) ; }

#define OSS_HINT_MARK_BRANCH_UNLIKELY(x) __builtin_expect((x),0)

extern "C"  unsigned long g_sqltCompTraceFlags[230+1] ;

#define pdGetCompTraceFlag(compID)   (g_sqltCompTraceFlags[(compID)])

#define pdTraceGetCompFlags( ecfID )  pdGetCompTraceFlag(ecfGetComponentIndex( ecfID ))

#define pdTraceInitLocalFlagNoCodepath( ecfID )  unsigned long pdTraceLocalFlag     = pdTraceGetCompFlags( ecfID ) ;     0

#define IF_TRACE_AND_DEBUG_HOOK if ( OSS_HINT_MARK_BRANCH_UNLIKELY(pdTraceLocalFlag & (1<<0x12)))

#define HOOK_INTO_OLD_TRACE_ENTRY(_ecfID) { pdTraceInitLocalFlagNoCodepath( _ecfID ); TRACE_ENTRY_DEBUG_HOOK( _ecfID );      }

#define TRACE_ENTRY_DEBUG_HOOK( _ecfID ) IF_TRACE_AND_DEBUG_HOOK { OSS_HINT_MARK_BASIC_BLOCK_INFREQUENT ; }

#define HOOK_INTO_TRACE_POINT

extern "C" void sqltEntry ( unsigned long  id ) ;

#define sqlt_fnc_entry(comp, fnc)                                          \
   {                                                                       \
      HOOK_INTO_TRACE_POINT                                                \
      HOOK_INTO_OLD_TRACE_ENTRY(fnc) ;                                     \
      if ( pdGetCompTraceFlag(comp) & PD_FLAG_FNC_ENTRY )              \
         sqltEntry((fnc)) ;                                    \
   }

#define sqlt_tmp_entry      sqlt_fnc_entry

struct sqlo_waitlist
{
   inline int semaphoreOp
   (
      const int op
   )
   {
      sqlt_tmp_entry(1, 1) ;

      int rc = 0 ;

      return rc ;
   }
} ;
