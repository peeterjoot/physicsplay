#!/usr/bin/perl

my @keys = (
   [
      'just\s*energy|ontario energy'
# blog only
   ],
   [
      'phy356|liboff|lowering|square well|commutator|pauli|raising|generator'
#https://sites.google.com/site/peeterjoot/math2010/phy356.pdf
   ],
   [
      'desai'
#Believed to be typos in Desai's QM Text
#http://sites.google.com/site/peeterjoot/math2010/desaiTypos.pdf
   ],
   [
      'phy456|fermi golden rule'
#https://sites.google.com/site/peeterjoot/math2011/phy456.pdf
   ],
   [
      'quantum|dirac'
   ],
   [
      'phy450|relativistic|poppitz|electrodynamics|four velocity|boost|lorentz force|retarded time|lorentz|lienard.*wiechert'
#https://sites.google.com/site/peeterjoot/math2011/phy450.pdf
   ],
#   [
#      'arxiv'
#Change of basis and Gram-Schmidt orthonormalization in special relativity
# http://arxiv.org/abs/1104.4829
#   ],
#Relativistic origins of the Schrodinger equation
   [
      'phy454|continuum|lame'
#https://sites.google.com/site/peeterjoot2/math2012/phy454.pdf
   ],
   [
      'banister|bannister|newel'
# blog only
   ],
   [
      'phy354|noether|lagrangian|hamiltonian|action|conjugate momenta|routh|classical mechanics|pendulum|canonical'
# not posted
   ],
   [
      'ud2a'
# blog only
   ],
   [
      'root|8200'
# blog only
   ],
   [
      'fence|sync|barrier|atomic|lwarx|stwcx'
#      An attempt to illustrate differences between memory ordering and atomic access
#      , http://sites.google.com/site/peeterjoot/math2009/atomic.pdf
#      A nice simple example of a memory barrier requirement
#      , https://sites.google.com/site/peeterjoot/math2010/atomicSimple.pdf
#      Timings and correctness issues for mutex release operations
#      http://sites.google.com/site/peeterjoot/math2010/mutexRelease.pdf      
   ],
   [
      'git'
# blog only
   ],
   [
      'gdb|scheduler-locking|dbx'
# blog only
   ],
   [
      'geometric|wedge|clifford|bivector'
# https://sites.google.com/site/peeterjoot/math2009/gabook.pdf
   ],
   [
      'align|padding'
# blog only
   ],
   [
      'nm|bsymbolic'
# blog only
   ],
   [
      'alias'
# blog only
   ],
   [
      'xargs|perl|awk'
# blog only
   ],
   [
      'joot|peeter|peter'
   ]
   #   ,'phy485'
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

   $out{$k} = "$k: $n\n$s\n\n" ;
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
