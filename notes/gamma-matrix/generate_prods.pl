$s=qq/
   cmatrix gAB(4,4) ;
   gAB = prod( gammaA, gammaB ) ;
   printit( "\\\\gamma^A \\\\gamma^B = ", gAB ) ;
/ ;

$t=qq/
   {
      cmatrix tAB(4,4) ;
      cmatrix gABC(4,4) ;

      tAB = prod( gammaA, gammaB ) ;
      gABC = prod( tAB, gammaC ) ;

      printit( "\\\\gamma^A \\\\gamma^B \\\\gamma^C = ", gABC ) ;
   }
/ ;

sub ii
{
  my ($ss, $i, $j, $k) = @_ ;

  $ss =~ s/A/$i/g ;
  $ss =~ s/B/$j/g ;
  $ss =~ s/C/$k/g ;

  print "$ss\n" ;
}

ii( $t, 1, 2, 3 ) ;
ii( $t, 2, 3, 0 ) ;
ii( $t, 3, 0, 1 ) ;
ii( $t, 0, 1, 2 ) ;

ii( $s, 0, 0, 666 ) ;
ii( $s, 1, 1, 666 ) ;
ii( $s, 2, 2, 666 ) ;
ii( $s, 3, 3, 666 ) ;

ii( $s, 0, 1, 666 ) ;
ii( $s, 1, 0, 666 ) ;

ii( $s, 0, 2, 666 ) ;
ii( $s, 2, 0, 666 ) ;

ii( $s, 0, 3, 666 ) ;
ii( $s, 3, 0, 666 ) ;

ii( $s, 1, 2, 666 ) ;
ii( $s, 2, 1, 666 ) ;

ii( $s, 1, 3, 666 ) ;
ii( $s, 3, 1, 666 ) ;

ii( $s, 2, 3, 666 ) ;
ii( $s, 3, 2, 666 ) ;
