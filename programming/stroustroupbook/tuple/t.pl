#!/usr/bin/perl

my ($a, $b, $c) = foo() ;

printf( "%0.1f $b $c\n", $a ) ;

exit 0 ;

sub foo
{
   return (1.0, "blah", 3) ;
}
