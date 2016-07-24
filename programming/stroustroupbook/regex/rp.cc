#include <regex.h>      
#include <iostream>     
#include <string>
#include <exception>
#include <array>

/** 
   A regular expression wrapper class that uses posix extended REs and provides some convience interfaces.
 */
class regex
{
   bool     m_compiled{} ;
   regex_t  m_regex{} ;

   /** 
      Compile the Re.

      \internal
    */
   inline void compile( const char * re ) ;

public:
   /**
      Exception state associated with a regcomp or regexec failure.
    */
   class exception : public std::exception
   {
      std::string s ;

   public:
      exception( const regex_t & r, int rc ) ;

      const char * what( ) const noexcept
      {
         return s.c_str() ;
      }
   } ;

   /**
      Construct a regex from the supplied string.
    */
   inline regex( const char * re ) ;

   /** returns true if matched */
   inline bool exec( const char * pat ) ;

   /**
      Match results and the string buffer that the match is coming from.

      This is a helper class for the exec() function.  The string that the exec 
      operates on is cached in this data structure.
    */
   template <size_t N>
   struct regmatch
   {
      std::array<regmatch_t, N>  m_matchResults{} ;
      const char *               m_pat ;

      /**
         Supply the string that the regex will operate on.
       */
      regmatch( const char * pat ) : m_pat( pat) {}

      /**
         Translate the posix regmatch_t offset info into a standalone string representation.
       */      
      std::string operator[]( const size_t i ) const
      {
         const regmatch_t & r = m_matchResults[ i ] ;
         size_t len = r.rm_eo - r.rm_so ;

         auto s = std::string( &m_pat[ r.rm_so ], len ) ;
         return s ;
      }
   } ;

   /**
      Execute the regular expression allowing for collection of the match results.
    */
   template <size_t N>
   inline bool exec( regmatch<N> & matchBuf ) ;

   ~regex()
   {
      regfree( &m_regex ) ;
   }
} ;

inline regex::exception::exception( const regex_t & r, int rc )
{
   char buf[128] ;

   regerror( rc, &r, buf, sizeof(buf) ) ;

   s = buf ;
}

inline void regex::compile( const char * re )
{
   /* Compile regular expression */
   int rc = regcomp( &m_regex, re, REG_EXTENDED ) ;
   if ( rc )
   {
      throw exception( m_regex, rc ) ;
   }

   m_compiled = true ;
}

inline bool regex::exec( const char * pat )
{
   /* Execute regular expression */
   int rc = regexec( &m_regex, pat, 0, NULL, 0 ) ;

   if ( rc && (rc != REG_NOMATCH) )
   {
      throw exception( m_regex, rc ) ;
   }

   return ( rc != REG_NOMATCH ) ;
}

template <size_t N>
inline bool regex::exec( regmatch<N> & matchBuf )
{
   /* Execute regular expression */
   int rc = regexec( &m_regex, matchBuf.m_pat, N, &matchBuf.m_matchResults[0], 0 ) ;

   if ( rc && (rc != REG_NOMATCH) )
   {
      throw exception( m_regex, rc ) ;
   }

   return ( rc != REG_NOMATCH ) ;
}

inline regex::regex( const char * re )
{
   compile( re ) ;
}

void fail()
try {
   // https://github.com/agordon/posix-libc-examples/blob/master/regex-examples.c : a bad regex:
   regex re( "hello([0-9*world" ) ;
}
catch ( std::exception & e )
{
   std::cerr << "fail: error: " << e.what() << '\n' ;
}

int main()
try {
   //regex re( R"(\q\a\x\y\e\f\g)" ) ;
#if 0
   // works on Linux, but not on Mac:
   regex re( R"((\S+)(\s+)(\S+))" ) ;
#else
   regex re( R"(([^[:space:]]+)([[:blank:]]+)([^[:space:]]+))" ) ;
#endif
   //regex re( "\\S+\\s\\S+" ) ;
   //regex re( "[^[:space:]]+[[:space:]][^[:space]]+" ) ;
   //regex re( "[[:space:]]+[[:space:]][[:space]]+" ) ;
   //regex re( "[:space:]+x[:space]+" ) ;
   //regex re( "[:space:]+x[:space]+" ) ;

   fail() ;

   const char * pat { "blah rah" } ;
   if ( re.exec( pat ) )
   {
      std::cout << "match: " << pat << '\n' ;
   }
   else
   {
      std::cout << "no match: '" << pat << "'\n" ;
   }

   regex::regmatch< 4 > m{ pat } ;
   if ( re.exec( m ) )
   {
      std::cout << "match: " << pat << '\n' ;

      std::cout << "match data\n" ;
      for ( size_t i{} ; i < m.m_matchResults.size() ; i++ )
      {
         std::cout << i << " : " << m[i] << '\n' ;
      }

      std::cout << pat << " -> " << m[3] << " " << m[1] << '\n' ;
   }
   else
   {
      std::cout << "no match: '" << pat << "'\n" ;
   }

   //const char * pat2 { "blahblah" } ;
   const char * pat2 { "   x   " } ;
   if ( re.exec( pat2 ) )
   {
      std::cout << "match: " << pat2 << '\n' ;
   }
   else
   {
      std::cout << "no match: '" << pat2 << "'\n" ;
   }

   return 0 ;
}
catch ( std::exception & e )
{
   std::cerr << "error: " << e.what() << '\n' ;

   return 1 ;
}
