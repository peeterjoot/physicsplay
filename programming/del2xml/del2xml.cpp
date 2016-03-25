#include <cstdio>
#include <string>
#include <cassert>
#include <cstring>
#include <vector>
#include <sstream>
#include <cstdlib>
#include <iostream>
#include <climits>
#include <fstream>
#include <cctype>
#include "commit.h"

#if defined _MSC_VER
   #define __STDC__ 1
#endif
   #include <getopt.h>

using namespace std ;

#if defined _MSC_VER
   #define mysnprintf _snprintf
#else
   #define mysnprintf snprintf
#endif

class csvToXml
{
   /** represents either a set of column tags from the first line, or the column data for a given row */
   typedef vector<string> columnData ;

   /*
     Values for columnTypeInfo::columnMetaDataType, one for each of:

        <Type>char</Type>
        <Type>date</Type>
        <Type>decimal</Type>
        <Type>integer</Type>
        <Type>smallint</Type>
        <Type>time</Type>
        <Type>timestamp</Type>
   */
   #define FLAG_CHAR_TYPE        1
   #define FLAG_DATE_TYPE        2
   #define FLAG_DECIMAL_TYPE     4
   #define FLAG_INTEGER_TYPE     8
   #define FLAG_SMALLINT_TYPE    16
   #define FLAG_TIME_TYPE        32
   #define FLAG_TIMESTAMP_TYPE   64

   /**
      As we navigate over the rows, collect stats on what we find on the columns so that we can pick an SQL type later.
    */
   struct columnTypeInfo
   {
      /** the final type determination */
      int   columnMetaDataType ;

      /** sum of the lengths of all the character data.  For varchar vs. char type determination (disabled) */
      int   charLen ;

      /** the maximum length of the all the rows for a column */
      int   sizes ;

      /** count how many times the data looks like integer */
      int   totalIntegerRowsForColumn ;

      /** count how many times the data looks like small (short) integer */
      int   totalSmallIntegerRowsForColumn ;

      /** count how many times the data looks like a date format */
      int   totalDateRowsForColumn ;

      /** count how many times the data looks like a time format */
      int   totalTimeRowsForColumn ;

      /** count how many times the data looks like a timestamp format */
      int   totalTimeStampRowsForColumn ;

      /** count how many times the data looks like a decimal format */
      int   totalDecimalRowsForColumn ;

      columnTypeInfo() : 
         columnMetaDataType(0),
         charLen(0),
         sizes(0),
         totalIntegerRowsForColumn(0),
         totalSmallIntegerRowsForColumn(0),
         totalDateRowsForColumn(0),
         totalTimeRowsForColumn(0),
         totalTimeStampRowsForColumn(0),
         totalDecimalRowsForColumn(0) 
      { }
   } ;

   /// for (now dead) varchar vs char column type picking logic.
   double                  m_varcharFraction ;

   /// names for the columns, picked from the first row of the .csv
   columnData              m_headers ;

   /// one vector element for each row of data after the first of the .csv.  Each row is a vector of column data (in string form)
   vector<columnData>      m_rows ;

   /// All the info used to pick the column data types (and what that pick is in the end.)

   vector<columnTypeInfo>  m_typeInfo ;

   /// The number of columns found in the first row of the .csv.  This must match the number of columns found in each subsequent row.
   int                     m_numTags ;

   /// The (single character) delimiter that has been passed to the driver to split each .csv line
   char                    m_delimiter ;

   string                  m_filename ;

   /// save the optional delimiter parameter if specified (or print the help)
   void parseArguments( int argc, char ** argv ) ;

   /// print the help and exit.
   void showHelpAndExit() ;

   /**
      \param rowIndex zero indexed.  Second line of the .csv has index 0.
    */
   void printOneDataRow( int rowIndex ) ;

   /**
      \param columnIndex.  Zero indexed column number.
    */
   void printOneColumnMetaData( int columnIndex ) ;

   /**
      Called from the driver for each line of input.
      Pushes another row onto m_rows and collects some of the column metadata as the row is parsed.
    */
   void consumeOneLine( const string & line ) ;

   /**
      helper function.  perform a dumb single character delimited split of a line into an array of strings

      \param e [out]
          The output string array.  Assumed empty to start with.

      \param del [in]
          The split delimiter.

      \param line [in]
          The string to split.
    */
   void split( vector<string> & e, char del, const string & line ) const ;

   // 
   // These all check the row counts, not the attribute that will be set based on these checks if true
   // (since that decision is also based on what other attributes match and the order of checking)
   //
   bool areRowsAllSmallInteger( int columnIndex ) const
   {
      return ( m_typeInfo[ columnIndex ].totalSmallIntegerRowsForColumn == m_rows.size() ) ;
   }

   bool areRowsAllInteger( int columnIndex ) const
   {
      return ( m_typeInfo[ columnIndex ].totalIntegerRowsForColumn == m_rows.size() ) ;
   }

   bool areRowsAllDecimal( int columnIndex ) const
   {
      return ( m_typeInfo[ columnIndex ].totalDecimalRowsForColumn == m_rows.size() ) ;
   }

   bool areRowsAllDate( int columnIndex ) const
   {
      return ( m_typeInfo[ columnIndex ].totalDateRowsForColumn == m_rows.size() ) ;
   }

   bool areRowsAllTime( int columnIndex ) const
   {
      return ( m_typeInfo[ columnIndex ].totalTimeRowsForColumn == m_rows.size() ) ;
   }

   bool areRowsAllTimeStamp( int columnIndex ) const
   {
      return ( m_typeInfo[ columnIndex ].totalTimeStampRowsForColumn == m_rows.size() ) ;
   }

   // these all increment the row count for this type:
   void recordOneSmallIntegerForColumn( int columnIndex )
   {
      m_typeInfo[ columnIndex ].totalSmallIntegerRowsForColumn++ ;
   }

   void recordOneIntegerForColumn( int columnIndex )
   {
      m_typeInfo[ columnIndex ].totalIntegerRowsForColumn++ ;
   }

   void recordOneDecimalForColumn( int columnIndex )
   {
      m_typeInfo[ columnIndex ].totalDecimalRowsForColumn++ ;
   }

   void recordOneDateForColumn( int columnIndex )
   {
      m_typeInfo[ columnIndex ].totalDateRowsForColumn++ ;
   }

   void recordOneTimeForColumn( int columnIndex )
   {
      m_typeInfo[ columnIndex ].totalTimeRowsForColumn++ ;
   }

   void recordOneTimeStampForColumn( int columnIndex )
   {
      m_typeInfo[ columnIndex ].totalTimeStampRowsForColumn++ ;
   }


public:
   csvToXml() :
      m_varcharFraction( 0.5 ),
      m_headers(),
      m_rows(),
      m_typeInfo(),
      m_numTags( 0 ),
      m_delimiter( ',' ),
      m_filename( )
   {
   }

   void driver( int argc, char ** argv ) ;
} ;

void csvToXml::split( vector<string> & e, char del, const string & line ) const
{
   stringstream ss( line ) ;
   string s;
   int columnNumber = 1 ;

   while ( getline( ss, s, del ) )
   {
      size_t l = s.length() ;

      string t ;
      const char * sv = s.c_str() ;

      for ( size_t i = 0 ; i < l ; i++ )
      {
         t.push_back( isprint( sv[i] ) ? sv[i] : ' ' ) ;
      }

      if ( t != s )
      {
         int rowNumber = m_rows.size() + 1 ;

         fprintf( stderr,
                  "Error: Row=%d, Column=%d: line:\n"
                  "\t'%s'\n"
                  "\tNon-printable characters found in string '%s'\n"
                  "\tConverted to '%s'\n",
                  rowNumber, columnNumber, line.c_str(), s.c_str(), t.c_str() ) ;
      }

      e.push_back( t ) ;

      columnNumber++ ;
   }
}

int main( int argc, char ** argv )
{
   csvToXml convert ;

   convert.driver( argc, argv ) ;

   return 0 ;
}

void csvToXml::driver( int argc, char ** argv )
{
   parseArguments( argc, argv ) ;

   printf( "<?xml version=\"1.0\" encoding=\"utf-8\"?>\n"
           "<DataSet xmlns=\"http://www.ibm.com/qmf\" xmlns:xsi=\"http://www.w3.org/2001/XMLSchema-instance\">\n"
           "\n"
           "  <ResultSet>\n"
           "    <MetaData>\n"
           "      <SourceDescription/>\n" ) ;

   string s ;
   fstream f ;

   if ( "" != m_filename )
   {
      f.open( m_filename.c_str() ) ;
   }

   if ( f.is_open() )
   {
      while ( getline( f, s ) )
      {
         consumeOneLine( s ) ;
      }
   }
   else
   {
      while ( getline( cin, s ) )
      {
         consumeOneLine( s ) ;
      }
   }

   printf( "      <ColumnsAmount>%d</ColumnsAmount>\n", m_numTags ) ;

   for ( int c = 0 ; c < m_numTags ; c++ )
   {
      printOneColumnMetaData( c ) ;
   }

   printf( "    </MetaData>\n"
           "    <Data>\n" ) ;

   for ( int r = 0 ; r < m_rows.size() ; r++ )
   {
      printOneDataRow( r ) ;
   }

   printf( "     </Data>\n"
           "  </ResultSet>\n"
           "\n"
           "  <Extensions/>\n"
           "\n"
           "</DataSet>\n" ) ;
}

void csvToXml::parseArguments( int argc, char ** argv )
{
   int c ;

   const struct option long_options[] = {
     { "help",       0, NULL, 'h' },
     { "file",       0, NULL, 'f' },
     { "delimiter",  1, NULL, 'd' },
     { NULL,         0, NULL, 0   }
   } ;

   while ( -1 != ( c = getopt_long( argc, argv, "hd:f:", long_options, NULL ) ) )
   { 
      switch ( c )
      {
         case 'd' :
         {
            if ( 1 == strlen( optarg ) )
            {
               m_delimiter = optarg[0] ;
            }
            else
            {
               printf( "%s: error: expected one character delimiter, found '%s'\n", argv[0], optarg ) ;

               showHelpAndExit() ;
            }

            break ;
         }
         case 'f' :
         {
            m_filename = optarg ;

            break ;
         }
         case 'h' :
         default:
         {
            showHelpAndExit() ;
         }
      } 
   }
}

void csvToXml::showHelpAndExit()
{
   printf( "del2xml [-h|--help] [-d Z|--delimiter=Z] [-f filename|--file=filename|< input] > output\n" 
           "\n"
           "-delimiter=Z - a one character delimiter (in this case Z).  Default delimiter is ',' (comma).\n" 
           "-filename=n - filename to read from.  If unspecified stdin is assumed.\n"
           "\n"
           "version: %s\n", commitString ) ;

// [-varfrac vcFraction]
//\t-varfrac vcFraction\tIf the size of the storage used in char representation times vcFraction
//\t                   \tis greater than the space required for the same data in varchar
//\t                   \tformat, use a varchar type instead of char.  vcFraction defaults to 0.5

   exit( 1 ) ;
}

void csvToXml::consumeOneLine( const string & line )
{
   vector<string> e ;

   split( e, m_delimiter, line ) ;

   int numColumns = e.size( ) ; 

   if ( m_numTags )
   {
      assert( numColumns == m_numTags ) ;

      m_rows.push_back( e ) ;

      for ( int columnIndex = 0 ; columnIndex < numColumns ; columnIndex++ )
      {
         string v = e[ columnIndex ] ;
         int l = v.length( ) ;

         // save for average/stddev len calculation if char (to decide for char vs varchar).
         m_typeInfo[ columnIndex ].charLen += l ;

         if ( m_typeInfo[ columnIndex ].sizes < l )
         {
            m_typeInfo[ columnIndex ].sizes = l ;
         }

         char * err = 0 ;
         long longValue = strtol( v.c_str(), &err, 10 ) ;

         if ( !err[0] )
         {
            recordOneIntegerForColumn( columnIndex ) ;

            if ( (longValue < SHRT_MAX) && (longValue > SHRT_MIN) )
            {
               recordOneSmallIntegerForColumn( columnIndex ) ;
            }
         }

         // Crude decimal predicate: can we convert input to double?
         double doubleValue = strtod( v.c_str(), &err ) ;

         if ( !err[0] )
         {
            recordOneDecimalForColumn( columnIndex ) ;
    
            // FIXME: would also have to figure out scale and precision before enabling.
         }

         {
            unsigned d = 0, m = 0, y = 0, hr = 0, min = 0, sec = 0, usec = 0 ;
            // 2012-03-14T10:28:53.205800
            // 2012-03-14
            int rc = sscanf( v.c_str(), "%04u-%02u-%02uT%02u:%02u:%02u.%06u", &y, &m, &d, &hr, &min, &sec, &usec ) ;

            if ( (3 <= rc) &&
                 (y != 0) &&
                 (m != 0) &&
                 (d != 0) &&
                 (d <= 31) &&
                 (m <= 12) &&
                 (y <= 9999) )
            {
               if ( 3 == rc )
               {
                  recordOneDateForColumn( columnIndex ) ;
               }
               else if ( (7 == rc) &&
                         (hr < 24) &&
                         (min < 60) &&
                         (sec < 60) &&
                         (usec < 1000000) )
               {
                  recordOneTimeStampForColumn( columnIndex ) ;
               }
            }
            else
            {
               // 09:29:40
               rc = sscanf( v.c_str(), "%02u:%02u:%02u", &hr, &min, &sec ) ;
               if ( (3 == rc) &&
                    (hr < 24) &&
                    (min < 60) &&
                    (sec < 60) )
               {
                  recordOneTimeForColumn( columnIndex ) ;
               }
            }
         }
      }
   }
   else
   {
      m_headers = e ;
      m_numTags = numColumns ;

      m_typeInfo.resize( numColumns ) ;
   }
}

void csvToXml::printOneColumnMetaData( int columnIndex )
{
   int            cpp   = columnIndex + 1 ;
   const char *   n     = m_headers[ columnIndex ].c_str() ;
   int            s     = m_typeInfo[ columnIndex ].sizes ;
   char           attr[ 256 ] ;

   if ( areRowsAllSmallInteger( columnIndex ) )
   {
      m_typeInfo[ columnIndex ].columnMetaDataType = FLAG_SMALLINT_TYPE ;

      mysnprintf( attr, sizeof(attr),
                  "<Type>smallint</Type>\n"
                  "        <Width>%d</Width>", s ) ;
   }
   else if ( areRowsAllInteger( columnIndex ) )
   {
      m_typeInfo[ columnIndex ].columnMetaDataType = FLAG_INTEGER_TYPE ;

      mysnprintf( attr, sizeof(attr),
                  "<Type>integer</Type>\n"
                  "        <Width>%d</Width>", s ) ;
   }
#if 0
   else if ( areRowsAllDecimal( columnIndex ) )
   {
      m_typeInfo[ columnIndex ].columnMetaDataType = FLAG_DECIMAL_TYPE ;

      // FIXME: http://stackoverflow.com/questions/2377174/how-do-i-interpret-precision-and-scale-of-a-number-in-a-database

      // on decimal detection, will need to record the max scale and max prec (and distinguish from integer since valid ints are also 
      // valid decimal)
      mysnprintf( attr, sizeof(attr),
                  "<Type>decimal</Type>\n"
                  "        <Scale>0</Scale>\n"
                  "        <Precision>%d</Precision>", s ) ;
   }
#endif
#if 1 // test.
   else if ( areRowsAllTimeStamp( columnIndex ) )
   {
      m_typeInfo[ columnIndex ].columnMetaDataType = FLAG_TIMESTAMP_TYPE ;

      mysnprintf( attr, sizeof(attr), 
                  "<Type>timestamp</Type>\n"
                  "        <Width>%d</Width>", s ) ;
   }
   else if ( areRowsAllDate( columnIndex ) )
   {
      m_typeInfo[ columnIndex ].columnMetaDataType = FLAG_DATE_TYPE ;

      mysnprintf( attr, sizeof(attr), 
                  "<Type>date</Type>\n"
                  "        <Width>%d</Width>", s ) ;
   }
   else if ( areRowsAllTime( columnIndex ) )
   {
      m_typeInfo[ columnIndex ].columnMetaDataType = FLAG_TIME_TYPE ;

      mysnprintf( attr, sizeof(attr), 
                  "<Type>time</Type>\n"
                  "        <Width>%d</Width>", s ) ;
   }
#endif
   else
   {
      m_typeInfo[ columnIndex ].columnMetaDataType = FLAG_CHAR_TYPE ;

#if 0 // varchar not available for ROSI

      int varcharSpace = m_typeInfo[ columnIndex ].charLen ;
      int charSpace = s * m_rows.size() ;

      // use varchar if it gets us at least a (by default) 50% savings in total space for the table.
      if ( varcharSpace < (charSpace * m_varcharFraction) )
      {
         mysnprintf( attr, sizeof(attr),
                     "<Type>varchar</Type>\n"
                     "        <Width>%d</Width>", s ) ;
      }
      else
#endif
      {
         mysnprintf( attr, sizeof(attr), 
                     "<Type>char</Type>\n"
                     "        <Width>%d</Width>", s ) ;
      }
   }

   printf( "      <ColumnDescription id=\"%d\">\n"
           "        <Name>%s</Name>\n"
           "        <Label>%s</Label>\n"
           "        %s\n"
           "        <Nullable>false</Nullable>\n"
           "        <Format>plain</Format>\n"
           "      </ColumnDescription>\n", cpp, n, n, attr ) ;
}

void csvToXml::printOneDataRow( int rowIndex )
{
   columnData & c = m_rows[ rowIndex ] ;

   printf( "      <Row id=\"%d\">\n", rowIndex ) ;

   for ( int columnIndex = 0 ; columnIndex < m_numTags ; columnIndex++ )
   {
      int cpp = columnIndex + 1 ;
      int sz = m_typeInfo[ columnIndex ].sizes ;

      string tmp = c[ columnIndex ] ;
      size_t f = (size_t)-1 ;

      for ( ; ; )
      {
         f = tmp.find( "&", f + 1 ) ;
         
         if ( string::npos == f )
         {
            break ;
         }

         tmp.replace( f, 1, "&amp;" ) ;
      }

      const char * cv = tmp.c_str() ;

      if ( FLAG_CHAR_TYPE == m_typeInfo[ columnIndex ].columnMetaDataType )
      {
         // space pad the char output, but not for any other column types.

         printf( "        <Cell id=\"%d\">%-*s</Cell>\n", cpp, sz, cv ) ;
      }
      else
      {
         printf( "        <Cell id=\"%d\">%s</Cell>\n", cpp, cv ) ;
      }
   }

   printf( "      </Row>\n" ) ;
}
