#include <cstdio>
#include <string>
#include <cassert>
#include <cstring>
#include <vector>
#include <sstream>
#include <cstdlib>
#include <iostream>

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

   /**
      As we navigate over the rows, collect stats on what we find on the columns so that we can pick an SQL type later.
    */
   struct columnTypeInfo
   {
      int   charLen ;
      int   sizes ;
      int   totalIntegersInColumn ;
      int   totalDateFormatsInColumn ;

      columnTypeInfo() : 
         charLen(0),
         sizes(0),
         totalIntegersInColumn(0),
         totalDateFormatsInColumn(0) 
      { }
   } ;

   double                  m_varcharFraction ;
   columnData              m_headers ;
   vector<columnData>      m_rows ;
   vector<columnTypeInfo>  m_typeInfo ;
   int                     m_numTags ;
   char                    m_delimiter ;

   void parseArguments( int argc, char ** argv ) ;
   void showHelpAndExit() ;
   void printOneDataRow( int rowIndex ) ;
   void printOneColumnMetaData( int c ) ;
   void consumeOneLine( const string & line ) ;

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
   if ( (2 == argc) && (1 == strlen(argv[1])) )
   {
      m_delimiter = argv[1][0] ;
   }
   else if ( argc > 1 )
   {
      showHelpAndExit() ;
   }

#if 0 // not implemented.
   if ( showHelp )
   {
      showHelpAndExit() ;
   }
#endif
}

void csvToXml::showHelpAndExit()
{
   printf( "del2xml [delimiter] < input > output\n" 
           "\n"
           "delimiter - a one character delimiter (like Z)\n" ) ;

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

         bool foundNonChar = 0 ;

         char * err = 0 ;
         strtol( v.c_str(), &err, 10 ) ;

         if ( !err[0] )
         {
            m_typeInfo[ i ].totalIntegersInColumn++ ;

            foundNonChar = 1 ;
         }

//         if ( v =~ /^(\d+)\.(\d+)/ )
//         {
//               m_decimal[ i ]++ ;
//
//               foundNonChar = 1 ;
//         }

#if 0
         if ( v =~ qr(^\d\d/\d\d/\d\d\d\d$) )
         {
            m_typeInfo[ i ].totalDateFormatsInColumn++ ;

            foundNonChar = 1 ;
         }
#endif

         if ( foundNonChar )
         {
            // ...
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

void csvToXml::printOneColumnMetaData( int c )
{
   int            cpp   = c + 1 ;
   const char *   n     = m_headers[ c ].c_str() ;
   int            s     = m_typeInfo[ c ].sizes ;
   char           attr[ 256 ] ;

   int numRows = m_rows.size() ;

   if ( m_typeInfo[ c ].totalIntegersInColumn == numRows )
   {
      mysnprintf( attr, sizeof(attr),
                  "<Type>integer</Type>\n"
                  "        <Width>%d</Width>", s ) ;
   }
#if 0
   elsif ( m_decimal[ c ] == numRows )
   {
      // FIXME: http://stackoverflow.com/questions/2377174/how-do-i-interpret-precision-and-scale-of-a-number-in-a-database

      // on decimal detection, will need to record the max scale and max prec (and distinguish from integer since valid ints are also 
      // valid decimal)
      mysnprintf( attr, sizeof(attr),
                  "<Type>decimal</Type>\n"
                  "        <Scale>0</Scale>\n"
                  "        <Precision>%d</Precision>", s ) ;
   }
   elsif ( m_dateformat[ c ] == numRows )
   {
      // FIXME: what attributes does date require?  May not have parsed in the correct format.  Don't enable without info.
      mysnprintf( attr, sizeof(attr), 
                  "<Type>date</Type>\n"
                  "        <Width>%d</Width>", s ) ;
   }
#endif
   else
   {
      int varcharSpace = m_typeInfo[ c ].charLen ;
      int charSpace = s * numRows ;

      // use varchar if it gets us at least a (by default) 50% savings in total space for the table.
      if ( varcharSpace < (charSpace * m_varcharFraction) )
      {
         mysnprintf( attr, sizeof(attr),
                     "<Type>varchar</Type>\n"
                     "        <Width>%d</Width>", s ) ;
      }
      else
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

   for ( int i = 0 ; i < m_numTags ; i++ )
   {
      int cpp = i + 1 ;
      int sz = m_typeInfo[ i ].sizes ;
      const char * cv = c[ i ].c_str() ;

      // FIXME: should varchar output be trailing space padded?  Integer and decimal probably shouldn't either.
      printf( "        <Cell id=\"%d\">%-*s</Cell>\n", cpp, sz, cv ) ;
   }

   printf( "      </Row>\n" ) ;
}
