#!/usr/bin/perl

my @keys = (
    'just\s*energy|ontario energy'
   ,'phy356|liboff|lowering|square well|commutator|pauli|raising|generator'
   ,'desai'
   ,'phy456|fermi golden rule'
   ,'quantum|dirac'
   ,'phy450|relativistic|poppitz|electrodynamics|four velocity|boost|lorentz force|retarded time|lorentz|lienard.*wiechert'
   ,'phy454|continuum|lame'
   ,'banister|bannister|newel'
#   ,'phy485'
   ,'phy354|noether|lagrangian|hamiltonian|action|conjugate momenta|routh|classical mechanics|pendulum|canonical'
   ,'ud2a'
   ,'root|8200'
   ,'fence|sync|barrier|atomic|lwarx|stwcx'
   ,'git'
   ,'gdb|scheduler-locking|dbx'
   ,'geometric|wedge|clifford|bivector'
   ,'align|padding'
   ,'nm|bsymbolic'
   ,'alias'
   ,'xargs|perl|awk'
   ,'joot|peeter|peter'
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

foreach my $k ( @keys )
{
   my $s = '' ;
   my $n = 0 ;

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
