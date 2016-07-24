#include <regex.h>      
#include <iostream>     
#include <string>
#include <exception>

class regex
{
   bool     m_compiled{} ;
   regex_t  m_regex{} ;

   inline void compile( const char * re ) ;

public:
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

   inline regex( const char * re ) ;

   /** returns true if matched */
   inline bool exec( const char * pat ) ;

#if 0
   bool matched() const
   {
      return m_matchRc ;
   }
#endif
   
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

inline regex::regex( const char * re )
{
   compile( re ) ;
}

#if 0
inline regex::regex( const char * re, const char * pat )
{
   compile( re ) ;

   exec( pat ) ;
}
#endif

int main()
try
{
   //regex re( R"(\q\a\x\y\e\f\g)" ) ;
   //regex re( R"(\S+\s\S+)" ) ;
   //regex re( "\\S+\\s\\S+" ) ;
   //regex re( "[^[:space:]]+[[:space:]][^[:space]]+" ) ;
   //regex re( "[[:space:]]+[[:space:]][[:space]]+" ) ;
   //regex re( "[:space:]+x[:space]+" ) ;
   regex re( "[:space:]+x[:space]+" ) ;

   const char * pat { "blah blah" } ;
   if ( re.exec( pat ) )
   {
      std::cout << "match: " << pat << '\n' ;
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
