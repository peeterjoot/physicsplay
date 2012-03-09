#!/usr/bin/perl

# a hack-ish script to grab the pdfs from the web page for phy354.
# Usage:
#./grabUrls.pl PHY354_files http://www.physics.utoronto.ca/~poppitz/epoppitz/ < "Advanced_Classical_Mechanics.htm"
#
my ($files, $filepath) = @ARGV ;
my %all = () ;

while (<>)
{
   my $line = $_ ;
   chomp $line ;

   my @strings = split( /["']/, $line ) ;

   my @urls = grep { /$files/ } @strings ;

   foreach (@urls)
   {
      next unless /pdf$/ ;

      if ( /^$files/ )
      {
         $all{"$filepath$_"}++ ;
      }
      else
      {
         $all{$_}++ ;
      }
   }
}

foreach (keys %all)
{
   my $filename = $_ ;
   $filename =~ s,.*/,, ; 

   unless ( -e "$filename" )
   {
      print "wget $_\n" ;
      system "wget $_" ;
   }
}
