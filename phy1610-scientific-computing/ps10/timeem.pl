#!/usr/bin/perl

collecttimes() ;

exit 0 ;

sub collecttimes
{
   #my %times = () ;

   my $ps10dir = "$ENV{HOME}/physicsplay/phy1610-scientific-computing/ps10" ;
   my $cfgpath = "$ps10dir/wavescalingtestparams.txt" ;
   #my $cfgpath = "$ps10dir/waveparamsnoio.txt" ;

   #print "running $ps10dir/wave1d $cfgpath\n" ;
   for ( my $t = 1 ; $t <= 32 ; $t++ )
   {
      my $tm = `mpirun -n $t $ps10dir/wave1d $cfgpath 2>&1 | grep Walltime | sort -k3 -n | tail -1` ; chomp $tm ;

      $tm =~ s/.*= *// ;
      $tm =~ s/ .*// ;

      #$times{$t} = $tm ; 
      print "$t,$tm\n" ;
   }

   #foreach my $t ( sort keys %times )
   #{
   #   print "$t $times{$t}\n" ;
   #}
}
