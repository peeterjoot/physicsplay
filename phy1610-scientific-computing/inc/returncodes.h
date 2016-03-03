/** \file returncodes.h
 */
#if !defined phy1610_returncodes_h_included
#define phy1610_returncodes_h_included

/**
   Return codes for simple executable.

   The type uses 'unsigned char' to force the exit code to fit in the
   waitpid waitstatus byte.
 */
enum class RETURNCODES : unsigned char
{
    SUCCESS       ///< exit code for successful exectution
   ,HELP          ///< exit code when -help (or bad option is supplied)
   ,PARSE_ERROR   ///< exit code if there's a parse error */
} ;

#endif
