#!/usr/bin/perl

my @keys = (
   [
      'just\s*energy|ontario energy',
      'http://peeterjoot.wordpress.com/tag/just-energy-canada'
   ],
   [
      'phy356|liboff|lowering|square well|commutator|pauli|raising|generator',
      'https://sites.google.com/site/peeterjoot/math2010/phy356.pdf'
   ],
   [
      'desai',
      'http://sites.google.com/site/peeterjoot/math2010/desaiTypos.pdf'
   ],
#   [
#      'phy456|fermi golden rule',
#      'https://sites.google.com/site/peeterjoot/math2011/phy456.pdf'
#   ],
   [
      'quantum|dirac',
      'https://sites.google.com/site/peeterjoot/math2011/phy356.pdf',
      'https://sites.google.com/site/peeterjoot/math2011/phy456.pdf'
   ],
   [
      'phy450|relativistic|poppitz|electrodynamics|four velocity|boost|lorentz force|retarded time|lorentz|lienard.*wiechert',
      'https://sites.google.com/site/peeterjoot/math2011/phy450.pdf',
      'https://sites.google.com/site/peeterjoot2/math2013/classicalmechanics.pdf'
   ],
#   [
#      'arxiv',
#      'http://arxiv.org/abs/1104.4829'
#   ],
   [
      'phy454|continuum|lame',
      'https://sites.google.com/site/peeterjoot2/math2012/phy454.pdf'
   ],
   [
      'banister|bannister|newel',
      'http://peeterjoot.wordpress.com/2010/06/06/fixing-a-loose-banister',
      'http://peeterjoot.wordpress.com/category/home-improvement'
   ],
   [
      'phy354|noether|lagrangian|hamiltonian|action|conjugate momenta|routh|classical mechanics|pendulum|canonical',
      'https://sites.google.com/site/peeterjoot2/math2013/classicalmechanics.pdf'
   ],
   [
      'ud2a',
      'http://peeterjoot.wordpress.com/2010/05/26/a-fun-and-curious-dig-gcc-generation-of-a-ud2a-instruction-sigill/'
   ],
   [
      'root|8200',
      'http://peeterjoot.wordpress.com/2009/10/02/how-to-get-a-root-shell-if-you-can-modify-code-that-runs-setuid-root',
      'http://peeterjoot.wordpress.com/2009/12/07/software-developer-spotted-on-8200-warden-property/'
   ],
   [
      'fence|sync|barrier|atomic|lwarx|stwcx',
#      An attempt to illustrate differences between memory ordering and atomic access
      'http://sites.google.com/site/peeterjoot/math2009/atomic.pdf',
#      A nice simple example of a memory barrier requirement
      'https://sites.google.com/site/peeterjoot/math2010/atomicSimple.pdf',
#      Timings and correctness issues for mutex release operations
      'http://sites.google.com/site/peeterjoot/math2010/mutexRelease.pdf'
   ],
   [
      'git',
      'http://peeterjoot.wordpress.com/2009/12/16/abusing-the-git-version-control-system-as-a-distributed-filesystem'
   ],
   [
      'gdb|scheduler-locking|dbx',
      'http://peeterjoot.wordpress.com/category/debugging/'
   ],
   [
      'geometric|wedge|clifford|bivector',
      'https://sites.google.com/site/peeterjoot/math2009/gabook.pdf'
   ],
   [
      'align|padding',
      'http://peeterjoot.wordpress.com/2009/11/11/c-structure-alignment-padding/'
   ],
   [
      'nm|bsymbolic',
      'http://peeterjoot.wordpress.com/2010/03/22/using-nm-to-track-down-the-origin-of-an-undefined-symbol/'
   ],
   [
      'alias',
      'http://peeterjoot.wordpress.com/2010/07/09/use-of-unions-to-deal-with-aliasing-problems/',
      'http://peeterjoot.wordpress.com/2009/11/14/c-pointer-aliasing-violations-and-aggressive-compiler-optimizations/'
   ],
   [
      'xargs',
      'http://peeterjoot.wordpress.com/2010/02/28/shell-tips-and-tricks-the-most-basic-stuff/'
   ],
   [
      'perl',
      'http://peeterjoot.wordpress.com/category/perl-and-general-scripting-hackery/'
   ],
#   [
#      'awk',
#      'http://peeterjoot.wordpress.com/2009/08/19/doing-awk-like-stuff-in-perl/'
#   ],
#   [
#      'phy485',
#      'https://sites.google.com/site/peeterjoot2/math2012/phy485.pdf'
#   ],
   [
      'joot|peeter|peter',
      ''
   ],
) ;

my $first = 1 ;
my %counts ;

while (<>)
{
   chomp ;

   if ( $first )
   {
      $first = 0 ;
   }
   else
   {
      s/,(\d\d\d)/$1/g ;
      s/\t(\d+)$// or die "unexpected input '$_'\n" ;

      $counts{$_} += $1 ;
   }
}

my %seen ;
my %out ;
my %outcount ;

foreach my $kk ( @keys )
{
   my $s = '' ;
   my $n = 0 ;

   my $k = $kk->[0] ;
   my @r = splice( @$kk, 1, scalar(@$kk) ) ;

   foreach ( sort { $counts{$b} <=> $counts{$a} } keys %counts )
   {
      if ( /$k/i )
      {
         unless ( $seen{$_} )
         {
            my $c = $counts{$_} ;
            $n += $c ;

            $s .= "\t$_\t$c\n" ;

            $seen{$_}++ ;
         }
      }
   }

   my $rr = join( "\n", @r ) ;

   $out{$k} = "$k: $n\n$s$rr\n\n" ;
   $outcount{$k} = $n ;
}

my $n = 0 ;
my $s = '' ;
foreach ( sort { $counts{$b} <=> $counts{$a} } keys %counts )
{
   unless ( $seen{$_} )
   {
      my $c = $counts{$_} ;
      $n += $c ;

      $s .= "\t$_\t$c\n" ;

      $seen{$_}++ ;
   }

   $out{'rest'} = "The rest: $n\n$s\n\n" ;
   $outcount{'rest'} = $n ;
}

foreach my $k ( sort { $outcount{$b} <=> $outcount{$a} } keys %out )
{
   print $out{$k} ;
}
