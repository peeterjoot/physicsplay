#!/usr/bin/perl

my $all = 0 ;
my $soldReport = 0 ;
my $countryReport = 1 ;
my $feetInOneMeter = 3.2808399 ;

my @keys ;

if ( $countryReport )
{
   push( @keys, 'Town' ) ;
}

push( @keys,
 'Type'
,'Bedrooms'
,'Kitchens'
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

while (<>)
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

foreach (@keys)
{
   print "$_\t" ;
}
print "\n" ;

$all =~ 
s,
Prepared\sby.*?</tbody></table>
(.*?^</tbody></table>)
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

   if ( 0 )
   {
      open my $fh, ">$info{MLS}.out" or die ;
      print $fh $debug ;
      close $fh ;
   }
   
   foreach (@keys)
   {
      print "$info{$_}\t" ;
   }
   print "\n" ;
}
