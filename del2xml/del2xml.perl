#!/usr/bin/perl

use strict ;
use warnings ;
use Getopt::Long ;
#use List::Util 'sum' ;

my $g_deltext ;
my $g_dollar ;
my $g_bPrintHelpAndExit ;
my $g_varcharFraction = 0.5 ;

GetOptions
( 
   'delimiter=s'     => \$g_deltext,
   'dollar!'         => \$g_dollar,
   'varfrac=f'       => \$g_varcharFraction,
   'help!'           => \$g_bPrintHelpAndExit,
) ;

if ( defined $g_bPrintHelpAndExit )
{
   print qq
(del2xml [-help] [-delimiter blah] [-dollar] [-varfrac vcFraction]

Options:
\t-dollar            \tUse '\$' as a delimiter.
\t-delimiter blah    \tUse 'blah' as a delimiter.
\t-varfrac vcFraction\tIf the size of the storage used in char representation times vcFraction
\t                   \tis greater than the space required for the same data in varchar
\t                   \tformat, use a varchar type instead of char.  vcFraction defaults to 0.5

Default delimiter is '[optional-spaces],[optional-spaces]'
) ;

   exit 1 ;
}

my $g_delimiter ;
if ( defined $g_dollar )
{
   $g_delimiter = qr(\$) ;
}
elsif ( defined $g_deltext )
{
   $g_delimiter = qr($g_deltext) ;
}
else
{
   $g_delimiter = qr(\s*,\s*) ; # opt-spaces comma opt-spaces
}

my @g_headers = () ;
my @g_rows = () ;
my @g_sizes = () ;

# categorization:
my @g_charLen = () ;
my @g_integer = () ;
my @g_decimalPrecision = () ;
my @g_decimalScale = () ;
my @g_dateformat = () ;

my $g_numTags ;
my $g_rowIter = 0 ;

print q(<?xml version="1.0" encoding="utf-8"?>
<DataSet xmlns="http://www.ibm.com/qmf" xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance">

  <ResultSet>
    <MetaData>
      <SourceDescription/>
) ;

while ( <> )
{
   chomp ; # take off the trailing newline character.

   consumeOneLine( $_ ) ;
}

print "      <ColumnsAmount>$g_numTags</ColumnsAmount>\n" ;

for ( my $c = 0 ; $c < $g_numTags ; $c++ )
{
   printOneColumnMetaData( $c ) ;
}

print q
(    </MetaData>
    <Data>
) ;

for ( my $r = 0 ; $r < $g_rowIter ; $r++ )
{
   printOneDataRow( $r, $g_rows[$r] ) ;
}

print q
(     </Data>
  </ResultSet>

  <Extensions/>

</DataSet>
) ;

exit 0 ;

sub consumeOneLine
{
   my ( $line ) = @_ ;

   my @e = split( $g_delimiter, $line ) ;
   my $numColumns = scalar( @e ) ; 

   if ( defined $g_numTags )
   {
      die "numColumns != numTags: $numColumns, $g_numTags\n" if ( $numColumns != $g_numTags ) ;

      $g_rows[$g_rowIter] = \@e ;

      my $i = 0 ;
      foreach (@e)
      {
         my $l = length( $_ ) ;

         # save for average/stddev len calculation if char (to decide for char vs varchar).
         $g_charLen[$i] += $l ;

         if ( $g_sizes[$i] < $l )
         {
            $g_sizes[$i] = $l ;
         }

         my $foundNonChar = 0 ;

         if ( $_ =~ /^\d+$/ )
         {
            $g_integer[$i]++ ;

            $foundNonChar = 1 ;
         }

#         if ( $_ =~ /^(\d+)\.(\d+)/ )
#         {
#               $g_decimal[$i]++ ;
#
#               $foundNonChar = 1 ;
#         }

         if ( $_ =~ qr(^\d\d/\d\d/\d\d\d\d$) )
         {
            $g_dateformat[$i]++ ;
            $foundNonChar = 1 ;
         }

         #if ( $foundNonChar )
         #{
         #   # ...
         #}

         $i++ ;
      }

      $g_rowIter++ ;
   }
   else
   {
      @g_headers = @e ;
      $g_numTags = $numColumns ;

      # zero init of all these counting arrays:
      for ( my $i = 0 ; $i < $numColumns ; $i++ )
      {
         $g_sizes[$i] = 0 ;
      }

      @g_charLen     = @g_sizes ;
      @g_integer     = @g_sizes ;
#      @g_decimal     = @g_sizes ;
      @g_dateformat  = @g_sizes ;
   }
}

sub printOneColumnMetaData
{
   my ( $c ) = @_ ;       

   my $cpp = $c + 1 ;
   my $n = $g_headers[ $c ] ;
   my $s = $g_sizes[ $c ] ;

   my $attr ;

   if ( $g_integer[$c] == $g_rowIter )
   {
      $attr = qq(<Type>integer</Type>
        <Width>$s</Width>) ;
   }
#   elsif ( $g_decimal[$c] == $g_rowIter )
#   {
#      # FIXME: http://stackoverflow.com/questions/2377174/how-do-i-interpret-precision-and-scale-of-a-number-in-a-database
#
#      # on decimal detection, will need to record the max scale and max prec (and distinguish from integer since valid ints are also 
#      # valid decimal)
#      $attr = qq(<Type>decimal</Type>
#        <Scale>0</Scale>
#        <Precision>$s</Precision>) ;
#   }
#   elsif ( $g_dateformat[$c] == $g_rowIter )
#   {
#      # FIXME: what attributes does date require?  May not have parsed in the correct format.  Don't enable without info.
#      $attr = qq(<Type>date</Type>
#        <Width>$s</Width>) ;
#   }
   else
   {
#      my $varcharSpace = $g_charLen[$c] ;
#      my $charSpace = $s * $g_rowIter ;
#
#      # use varchar if it gets us at least a (by default) 50% savings in total space for the table.
#      if ( $varcharSpace < ($charSpace * $g_varcharFraction) )
#      {
#      $attr = qq(<Type>varchar</Type>
#        <Width>$s</Width>) ;
#      }
#      else
      {
      $attr = qq(<Type>char</Type>
        <Width>$s</Width>) ;
      }
   }

   print qq
(      <ColumnDescription id="$cpp">
        <Name>$n</Name>
        <Label>$n</Label>
        $attr
        <Nullable>false</Nullable>
        <Format>plain</Format>
      </ColumnDescription>
) ;
}

sub printOneDataRow
{
   my ( $r, $cr ) = @_ ;
   my @c = @$cr ;

   print qq(      <Row id="$r">\n) ;

   for ( my $i = 0 ; $i < $g_numTags ; $i++ )
   {
      my $cpp = $i + 1 ;
      my $sz = $g_sizes[$i] ;
      my $cv = $c[$i] ;

      # FIXME: should varchar output be trailing space padded?  Integer and decimal probably shouldn't either.
      my $v = sprintf( "%-${sz}s", $cv ) ;

      print qq(        <Cell id="$cpp">$v</Cell>\n) ;
   }

   print qq(      </Row>\n) ;
}
