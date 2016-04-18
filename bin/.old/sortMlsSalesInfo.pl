#!/usr/bin/perl

use strict ;
use warnings ;
use Getopt::Long;

my $soldReport = 0 ;
my $countryReport = 0 ;
my $debugMode = 0 ;
my $filename ;
my $showUsage = 0 ;
my $skipHeader = 0 ;

GetOptions(
   'countryReport!'     => \$countryReport,
   'debugMode!'         => \$debugMode,
   'skipHeader!'        => \$skipHeader,
   'soldReport!'        => \$soldReport,
   'filename=s'         => \$filename,
   'help!'              => \$showUsage,
) ;

if ( $showUsage or !defined $filename )
{
   die "usage: ~/bin/sortMlsSalesInfo.pl -f filename [-debug] [-countryReport] [-soldReport] [-help]\n"
}

my @keys ;
my $all = '' ;
my $feetInOneMeter = 3.2808399 ;

if ( $countryReport )
{
   push( @keys, 'Town' ) ;
}

push( @keys,
 'Type'
,'Bedrooms'
,'Total Bedrooms'
,'Kitchens'
,'Total Kitchens'
,'Garage Type'
,'Garage Spaces'
,'Parking Spaces'
) ;

# sales info
if ( $soldReport )
{
   push( @keys,
         'Sold',
         'List',
         'DOM',
         'Contract Date', 
         'Sold Date',
         'Orig Price' ) ;
}
else
{
   push( @keys, 'List', 'DOM', 'Possession' ) ;
}

# auxillary matching info:
push(@keys, 
 'Taxes'
,'Approx Square Ft'
,'Rooms'
,'Total Rooms'
,'Lot Size'
,'Basement'

# id:
,'MLS'
,'Address'

# misc:
,'Intersection'
#,'Laundry Level'
) ;

if ( $countryReport )
{
   push( @keys, 'Exterior', 'Water' ,'Sewers' ) ;
}

push( @keys, 'Reportname', 'Url', 'Comments' ) ;

open my $fh, "<$filename" or die "could not open file '$filename'\n" ;

while (<$fh>)
{
   s/&nbsp;/ /g ;
   s/&amp;/&/g ;
   s/width="\d+%"//g ;
   s/\s*For Sale//g ;
   s/border="\d+"//g ;
   s/align=".*?"//g ;
   s/<br>//g ;
#   s/^\s+//g ;
   $all .= $_ ;
}
close $fh ; 

unless ( $skipHeader )
{
   foreach (@keys)
   {
      print "$_\t" ;
   }
   print "\n" ;
}

#$all =~ 
#s,
#Prepared\sby.*?</tbody></table>
#(.*?^</tbody></table>)
#.*?Toronto\sReal\sEstate,foo($1),smegx ;

$all =~ 
s,
Prepared\sby.*?</table>
(.*?^</table>)
.*?Toronto\sReal\sEstate,foo($1),smegx ;

exit 0 ;

sub foo
{
   my $a = "@_" ;
   my $n = "@_" ;
   my %info ;

   if ( $n =~ /MLS.:*\s(\w\d+)/smg )
   {
      $info{MLS} = $1 ;
   }
   elsif ( $n =~ /^\s+(\w\d+)\s*$/smg )
   {
      $info{MLS} = $1 ;
   }
   else
   {
      die "NO MLS: $a" ;
   }

   $a =~ s,< *font.*?> *(.*?)</font>,$1,msg ;

# strip out the big header:
   $a =~ s,<div.*?>.*?</div>.*?^\s+<tbody>,,msg ;

# less whitespace
   $a =~ s/^\s\s\s/ /msg ;

   my @tr ;
   my $debug = '' ;

# hack.  For the non-sold input the <tr> split is wrong:
#$a = s,<td rowspan="2" v><!-- GetPHOTO\(Full_P\) --><tr>,,smg ;

   $a =~ s|<tr>(.*?)</tr>|push(@tr, $1)|smeg ;

   foreach (@tr)
   {
      $debug .= "tr: $_" ;

      if ( s/<font.*?".*?"\s*>// )
      {
         s,</fon[gt]>,,smg ;
      }

#      $debug .= "tr2: $_" ;
# trouble parsing a record of the following form:?
#				<tr>
#					<td colspan="3"><font style="font: bold 9pt">2091 Gerrard St E&nbsp;&nbsp;</font></td>
#					<td><font style="font: bold 9pt">$469,000</font></td>
#				</tr>

# address, sale price
      if ( m,GetPHOTO.*?<td.*?>(.*?)</td>.*Sold:.*?<td *>(.*?)</td>,sm )
      {
         $info{Address} = $1 ;
         $info{Sold} = $2 ;
      }
      elsif ( m,<td.*?>(.*?)</td>.*List:.*<td *>(.*?)</td>,sm )
      {
         # postal code and other stuff
         $info{Address} .= " $1" ;
         $info{List} = $2 ;
      }
      elsif ( m@
<td.*?>.*<tr>.*?        # hack
<td.*?>(.*?)</td>.*?
<td.*?>(\$\d+,\d\d\d)</td> # NOTE: doesn't work for 1000000+ houses
@smx )
      {
         $info{Address} = $1 ;
         $info{List} = $2 ;
#print "XX: $info{Address} ; $info{List} \n" ;
      }
      elsif ( m@<td.*?>(.*,\s*Ontario.*?)</td>@sm )
      {
         # postal code and other stuff
         $info{Address} .= " $1" ;
      }
      elsif ( m,<th.*?>Orig Price:.*?<td.*?>(.*?)</td>.*Taxes:</th>.*?<td.*?>(.*?)</td>,sm )
      {
         $info{'Orig Price'} = $1 ;
         $info{Taxes} = $2 ;
      }
# 		<th>Expiry Date:</th>
# 		<td>9/30/2010</td>
# 		<th>Closing Date:</th>
# 		<td>6/18/2010</td>
# 		<th>Original Price:</th>
# 		<td>$338,000</td>
      elsif ( m,
Original.Price:.*?<td.*?>(.*?)</td>.*?
,smx )
      {
         $info{'Orig Price'} = $1 ;
      }
##
# 		<th >SPIS:</th>
# 		<td >N</td>
# 		<th >DOM:</th>
# 		<td >12</td>
#  		<th >Taxes:</th>
# 		<td >$2,487.24/2010</td>
#  		<th >Last Status:</th>
# 		<td >Sld</td>
#
      elsif ( m,
SPIS:.*?<td.*?>(.*?)</td>.*?
DOM:.*?<td.*?>(.*?)</td>.*?
Taxes:.*?<td.*?>(.*?)</td>.*?
,smx )
      {
         $info{SPIS} = $1 ;
         $info{DOM} = $2 ;
         $info{Taxes} = $3 ;
      }
      elsif ( m,
SPIS:.*?<td.*?>(.*?)</td>.*?
Taxes:.*?<td.*?>(.*?)</td>.*?
,smx )
      {
         $info{SPIS} = $1 ;
         $info{Taxes} = $2 ;
      }
      elsif ( m,
DOM:.*?<td.*?>(.*?)</td>.*?
Contract:.*?<td.*?>(.*?)</td>.*?
Sold:.*?<td.*?>(.*?)</td>,smx )
      {
         $info{DOM} = $1 ;
         $info{'Contract Date'} = $2 ;
         $info{'Sold Date'} = $3 ;
      }
#
#      <th >Contract Date:</th>
#      <td >5/7/2010</td>
#      <th >Sold Date:</th>
#      <td >5/19/2010</td>
#      <th >Leased Terms:</th>
#      <td > </td>
#
      elsif ( m,
Contract.Date:.*?<td.*?>(.*?)</td>.*?
Sold.Date:.*?<td.*?>(.*?)</td>,smx )
      {
         $info{'Contract Date'} = $1 ;
         $info{'Sold Date'} = $2 ;
      }
      elsif ( m,
Taxes:.*?<td.*?>(.*?)</td>.*?
,smx )
      {
         $info{Taxes} = $1 ;
      }
      elsif ( m,
MLS.:.*?<td.*?>(.*?)</td>.*?
DOM:.*?<td.*?>(.*?)</td>.*?
Possession:.*?<td.*?>(.*?)</td>.*?
,smx )
      {
#         $info{MLS} = $1 ;
         $info{DOM} = $2 ;
         $info{Possession} = $3 ;
      }
      elsif ( m,
MLS.:.*?<td.*?>(.*?)</td>.*?
Possession:.*?<td.*?>(.*?)</td>.*?
,smx )
      {
#         $info{MLS} = $1 ;
         $info{Possession} = $2 ;
      }
      elsif ( m,
<td.*?>(.*?)</td>.*
Fronting\sOn:.*?<td.*?>(.*?)</td>.*?
Rooms:.*?<td.*?>(.*?)</td>.*?
               ,smx )
      {
         # fronting info just to find this record.
         $info{Type} = $1 ;
         $info{Rooms} = $3 ;
      }
      elsif ( m,
Bedrooms:.*?<td.*?>(.*?)</td>
               ,smx )
      {
         $info{Bedrooms} = $1 ;
      }
      elsif ( m,
Dir/Cross\sSt:.*?<td.*?>(.*?)</td>.*
Washrooms:.*?<td.*?>(.*?)</td>
               ,smx )
      {
         $info{Intersection} = $1 ;
      }
      elsif ( m,
Lot:.*?<td.*?>(.*?)</td>
               ,smx )
      {
         my $sz = $1 ;

         if ( $sz =~ /(.*)X(.*)Metres/ )
         {
            my ($x, $y) = ($1, $2 ) ;

            $x *= $feetInOneMeter ;
            $y *= $feetInOneMeter ;

            $info{'Lot Size'} = sprintf("%.2g,%.2g Feet", $x, $y) ;
         }
         else
         {
            $info{'Lot Size'} = $sz ;
         }
      }
      elsif ( m,
Kitchens:.*?<td.*?>(.*?)</td>
               ,smx )
      {
         $info{Kitchens} = $1 ;
      }
      elsif ( m,
Basement:.*?<td.*?>(.*?)</td>
               ,smx )
      {
         $info{Basement} = $1 ;
      }
      elsif ( m,
Apx\sSqft:.*?<td.*?>(.*?)</td>
               ,smx )
      {
         $info{'Approx Square Ft'} = $1 ;
      }
      elsif ( m,
Laundry\sLev:.*?<td.*?>(.*?)</td>
               ,smx )
      {
         $info{'Laundry Level'} = $1 ;
      }
      elsif ( m,
Exterior:.*?<td.*?>(.*?)</td>
               ,smx )
      {
         $info{Exterior} = $1 ;
      }
      elsif ( m,
GarType/Spaces:.*?<td.*?>(.*?)</td>
               ,smx )
      {
         my $g = $1 ;
         $g =~ m,(.*?)/(.*), ;

         $info{'Garage Type'} = $1 ;
         $info{'Garage Spaces'} = $2 ;
      }
      elsif ( m,
Parking\sSpaces:.*?<td.*?>(.*?)</td>
               ,smx )
      {
         $info{'Parking Spaces'} = $1 ;
      }
      elsif ( m,
Water:.*?<td.*?>(.*?)</td>
               ,smx )
      {
         $info{Water} = $1 ;
      }
      elsif ( m,
Sewers:.*?<td.*?>(.*?)</td>
               ,smx )
      {
         $info{Sewers} = $1 ;
      }
   }

   $info{Address} =~ s/\n/ /smg ;
   $info{Address} =~ s/\r/ /smg ;

   if ( $info{Address} =~ /Stouf/ )
   {
      $info{Town} = 'Stouffville' ;
   }
   elsif ( $info{Address} =~ /Markham/ )
   {
      $info{Town} = 'Markham' ;
   }
   elsif ( $info{Address} =~ /Claremont/ )
   {
      $info{Town} = 'Claremont' ;
   }

   if ( $debugMode )
   {
      open my $fh, ">$info{MLS}.out" or die ;
      print $fh $debug ;
      close $fh ;
   }
   
   $info{'Reportname'} = $filename ;

   my $totalBedrooms = eval( $info{'Bedrooms'} ) ;
   $info{'Total Bedrooms'} = $totalBedrooms ;

   my $totalKitchens = eval( $info{'Kitchens'} ) ;
   $info{'Total Kitchens'} = $totalKitchens ;

   my $totalRooms = eval( $info{'Rooms'} ) ;
   $info{'Total Rooms'} = $totalRooms ;

   $info{'List'} =~ s/\$// ;
   $info{'List'} =~ s/,//g ;
   $info{'List'} /= 1000 ;

   foreach (@keys)
   {
      print "$info{$_}\t" ;
   }
   print "\n" ;
}
