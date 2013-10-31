#include <cstdio>
#include <string>
#include <cassert>
#include <cstring>
#include <vector>
#include <sstream>
#include <cstdlib>
#include <iostream>
#include <climits>
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
         totalDateRowsForColumn(0) 
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
   static void split( vector<string> & e, char del, const string & line )
   {
      stringstream ss( line ) ;
      string s;

      while ( getline( ss, s, del ) )
      {
         e.push_back( s ) ;
      }
   }

public:
   csvToXml() :
      m_varcharFraction( 0.5 ),
      m_headers(),
      m_rows(),
      m_typeInfo(),
      m_numTags( 0 ),
      m_delimiter( ',' )
   {
   }

   void driver( int argc, char ** argv ) ;
} ;

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

   // with an arg parser, would make sense to allow cin to be a named file.
   while ( getline( cin, s ) )
   {
      consumeOneLine( s ) ;
   }

   printf( "      <ColumnsAmount>%d</ColumnsAmount>\n", m_numTags ) ;

   for ( int c = 0 ; c < m_numTags ; c++ )
   {
      printOneColumnMetaData( c ) ;
   }

   printf( "    </MetaData>\n"
           "    <Data>\n" ) ;

   int numRows = m_rows.size() ;

   for ( int r = 0 ; r < numRows ; r++ )
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
     { "delimiter",  1, NULL, 'd' },
     { NULL,         0, NULL, 0   }
   } ;

   while ( -1 != ( c = getopt_long( argc, argv, "hd:", long_options, NULL ) ) )
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
   printf( "del2xml [--help] [--delimiter=Z] < input > output\n" 
           "\n"
           "-delimiter Z - a one character delimiter (in this case Z).  Default delimiter is ',' (comma)\n" 
           "\n"
           "version: %s\n", commitString ) ;

//(del2xml [-help] [-delimiter blah] [-dollar] [-varfrac vcFraction]
//\t-dollar            \tUse '\$' as a delimiter.
//\t-varfrac vcFraction\tIf the size of the storage used in char representation times vcFraction
//\t                   \tis greater than the space required for the same data in varchar
//\t                   \tformat, use a varchar type instead of char.  vcFraction defaults to 0.5
//
//Default delimiter is '[optional-spaces],[optional-spaces]'

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

      for ( int i = 0 ; i < numColumns ; i++ )
      {
         string v = e[ i ] ;
         int l = v.length( ) ;

         // save for average/stddev len calculation if char (to decide for char vs varchar).
         m_typeInfo[ i ].charLen += l ;

         if ( m_typeInfo[ i ].sizes < l )
         {
            m_typeInfo[ i ].sizes = l ;
         }

         char * err = 0 ;
         long longValue = strtol( v.c_str(), &err, 10 ) ;

         if ( !err[0] )
         {
            m_typeInfo[ i ].totalIntegerRowsForColumn++ ;

            if ( (longValue < SHRT_MAX) && (longValue > SHRT_MIN) )
            {
               m_typeInfo[ i ].totalSmallIntegerRowsForColumn++ ;
            }
         }

         // Crude decimal predicate: can we convert input to double?
         double doubleValue = strtod( v.c_str(), &err ) ;

         if ( !err[0] )
         {
            m_typeInfo[ i ].totalDecimalRowsForColumn++ ;
    
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
                  m_typeInfo[ i ].totalDateRowsForColumn++ ;
               }
               else if ( (7 == rc) &&
                         (hr < 24) &&
                         (min < 60) &&
                         (sec < 60) &&
                         (usec < 1000000) )
               {
                  m_typeInfo[ i ].totalTimeStampRowsForColumn++ ;
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
                  m_typeInfo[ i ].totalTimeRowsForColumn++ ;
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

   int numRows = m_rows.size() ;

   if ( m_typeInfo[ columnIndex ].totalSmallIntegerRowsForColumn == numRows )
   {
      m_typeInfo[ columnIndex ].columnMetaDataType = FLAG_SMALLINT_TYPE ;

      mysnprintf( attr, sizeof(attr),
                  "<Type>smallint</Type>\n"
                  "        <Width>%d</Width>", s ) ;
   }
   else if ( m_typeInfo[ columnIndex ].totalIntegerRowsForColumn == numRows )
   {
      m_typeInfo[ columnIndex ].columnMetaDataType = FLAG_INTEGER_TYPE ;

      mysnprintf( attr, sizeof(attr),
                  "<Type>integer</Type>\n"
                  "        <Width>%d</Width>", s ) ;
   }
#if 0
   elsif ( m_decimal[ columnIndex ] == numRows )
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
   else if ( m_typeInfo[ columnIndex ].totalTimeStampRowsForColumn == numRows )
   {
      m_typeInfo[ columnIndex ].columnMetaDataType = FLAG_TIMESTAMP_TYPE ;

      mysnprintf( attr, sizeof(attr), 
                  "<Type>timestamp</Type>\n"
                  "        <Width>%d</Width>", s ) ;
   }
   else if ( m_typeInfo[ columnIndex ].totalDateRowsForColumn == numRows )
   {
      m_typeInfo[ columnIndex ].columnMetaDataType = FLAG_DATE_TYPE ;

      mysnprintf( attr, sizeof(attr), 
                  "<Type>date</Type>\n"
                  "        <Width>%d</Width>", s ) ;
   }
   else if ( m_typeInfo[ columnIndex ].totalTimeRowsForColumn == numRows )
   {
      m_typeInfo[ columnIndex ].columnMetaDataType = FLAG_TIME_TYPE ;

      mysnprintf( attr, sizeof(attr), 
                  "<Type>time</Type>\n"
                  "        <Width>%d</Width>", s ) ;
   }
   else
   {
      m_typeInfo[ columnIndex ].columnMetaDataType = FLAG_CHAR_TYPE ;

#if 0 // varchar not available for ROSI

      int varcharSpace = m_typeInfo[ columnIndex ].charLen ;
      int charSpace = s * numRows ;

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
      const char * cv = c[ columnIndex ].c_str() ;

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
