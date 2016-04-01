#!/usr/bin/perl

# some selected thread numbers for scaling tests
my @threadrange = (1, 2, 4, 6, 8) ;
my @outtime = ( 1, 0.1, 10, 20, 33 ) ;

system( "rm -f params* output* merged*" ) ;

foreach ( @outtime )
{
   runcfg( $_ ) ;
}

exit 0 ;

sub runcfg
{
   my ($outtime) = @_ ;
   my @methods = ( 'serial', 'threaded', 'multifile' ) ;
   my %cfglines = (
      'serial'    => '',
      'threaded'  => "threadedIO = 1\n",
      'multifile' => "parallelIO = 1\n" ) ;

   foreach my $iomode ( @methods )
   {
      my %times = () ;
      my $cfgpath = "params_${iomode}_outtime_$outtime.txt" ;
      my $outfilebase = "output_${iomode}_outtime_${outtime}_" ;

      my $cfgline = $cfglines{ $iomode } ;

      my $cfgdata = "c = 1\n" .
                    "tau = 20.0\n" .
                    "x1 = -26.0\n" .
                    "x2 = 26.0\n" .
                    "runttime = 100.0\n" .
                    "dx = 0.01\n" .
                    "outtime = $outtime\n" .
                    "filename = $outfilebase\n" .
                    "graphics = 0\n" .
                    $cfgline .
                    "" ;

      open my $fh, ">$cfgpath" or die ;
      print $fh $cfgdata ;
      close $fh or die ;

      my $ps9dir = "$ENV{HOME}/physicsplay/phy1610-scientific-computing/hw9" ;

      print "running $ps9dir/wave1d $cfgpath\n" ;

      foreach my $t (@threadrange)
      {
         $ENV{OMP_NUM_THREADS} = $t ;

         my $tm = `$ps9dir/wave1d $cfgpath | grep Walltime` ; chomp $tm ;

         $tm =~ s/.*= *// ;
         $tm =~ s/ .*// ;

         $times{$t} = $tm ; 

         print( "# cat $outfilebase* > merged$outfilebase.out.$t\n" ) ;
         system( "cat $outfilebase* > merged$outfilebase.out.$t" ) ;

         print( "# diff merged$outfilebase.out.$t mergedoutput_serial_outtime_${outtime}_.out.1\n" ) ;
         system( "diff merged$outfilebase.out.$t mergedoutput_serial_outtime_${outtime}_.out.1" ) ;

         my $rc = $? >> 8 ;
         if ( $rc eq 0 )
         {
            print( "# rm $outfilebase*\n" ) ;
            system( "rm $outfilebase*" ) ;

            if ( $t > 1 )
            {
               print( "# rm merged$outfilebase.out.$t\n" ) ;
               system( "rm merged$outfilebase.out.$t" ) ;
            }
         }
      }

      foreach my $t ( sort keys %times )
      {
         print "$outtime $t $iomode $times{$t}\n" ;
      }
   }
}
