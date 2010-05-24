#!/usr/bin/perl

my $all = 0 ;

my @keys = (
 "Type"
,"Bedrooms"
,"Kitchens"
,"Garage Type"
,"Garage Spaces"
,"Parking Spaces"

# sales info
,"Sold"
,"List"
,"DOM"
,"Contract Date"
,"Sold Date"
,"Orig Price"

# auxillary matching info:
,"Taxes"
,"Approx Square Ft"
,"Rooms"
,"Lot Size"
,"Basement"

# id:
,"MLS"
,"Address"

# misc:
,"Intersection"
,"Laundry Level"
,"Exterior"
,"Water"
,"Sewers"
) ;

while (<>)
{
   s/&nbsp;/ /g ;
   s/width="\d+%"//g ;
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

   if ( $n =~ /MLS.:*\s(N\d+)/smg )
   {
      $n = $1 ;
   }
   elsif ( $n =~ /^\s+(N\d+)\s*$/smg )
   {
      $n = $1 ;
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
   $a =~ s|<tr>(.*?)</tr>|push(@tr, $1)|smeg ;

   my %info ;
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
      elsif ( m,<th.*?>Orig Price:.*?<td.*?>(.*?)</td>.*Taxes:</th>.*?<td.*?>(.*?)</td>,sm )
      {
         $info{"Orig Price"} .= $1 ;
         $info{Taxes} = $2 ;
      }
      elsif ( m,
DOM:.*?<td.*?>(.*?)</td>.*?
Contract:.*?<td.*?>(.*?)</td>.*?
Sold:.*?<td.*?>(.*?)</td>,smx )
      {
         $info{DOM} .= $1 ;
         $info{"Contract Date"} = $2 ;
         $info{"Sold Date"} = $3 ;
      }
      elsif ( m,
<td.*?>(.*?)</td>.*
Fronting\sOn:.*?<td.*?>(.*?)</td>.*?
Rooms:.*?<td.*?>(.*?)</td>.*?
               ,smx )
      {
         # fronting info just to find this record.
         $info{Type} .= $1 ;
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
         $info{"Lot Size"} = $1 ;
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
         $info{"Approx Square Ft"} = $1 ;
      }
      elsif ( m,
Laundry\sLev:.*?<td.*?>(.*?)</td>
               ,smx )
      {
         $info{"Laundry Level"} = $1 ;
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

         $info{"Garage Type"} = $1 ;
         $info{"Garage Spaces"} = $2 ;
      }
      elsif ( m,
Parking\sSpaces:.*?<td.*?>(.*?)</td>
               ,smx )
      {
         $info{"Parking Spaces"} = $1 ;
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

   $info{MLS} = $n ;
   $info{Address} =~ s/\n/ /smg ;
   $info{Address} =~ s/\r/ /smg ;

   if ( 0 )
   {
      open my $fh, ">$n.out" or die ;
      print $fh $debug ;
      close $fh ;
   }
   
   foreach (@keys)
   {
      print "$info{$_}\t" ;
   }
   print "\n" ;
}
