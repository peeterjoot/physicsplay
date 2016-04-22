my $header =
"
\\qquad\\begin{tabular}{ | l | l | l | l | l |}
\\hline
" ;

my $footer 
=
"\\end{tabular}" ;

my $legend = 
"XW & SW & XR & S & X \\\\
\\hline
" ;

print "$header$legend$footer" ;

my %w = ( 
0 => '0',
1 => 'N'
) ;

my $acc = 0 ;
for ( my $x = 0 ; $x <= 1 ; $x++ )
{
   for ( my $s = 0 ; $s <= 2 ; $s++ )
   {
      for ( my $xr = 0 ; $xr <= 1 ; $xr++ )
      {
         for ( my $sw = 0 ; $sw <= 1 ; $sw++ )
         {
            for ( my $xw = 0 ; $xw <= 1 ; $xw++ )
            {
               next if ( $x and $s) ;

               if ( $acc % 2 == 0 )
               {
                  print "\\par\n" if ( $acc % 8 == 0 ) ;

                  print $header ;
               }

               print "$w{$xw} & $w{$sw} & $xr & $s & $x \\\\
\\hline
" ;

               if ( $acc % 2 == 1 )
               {
                  print $footer ;
               }

               $acc++ ;
            }
         }
      }
   }
}

