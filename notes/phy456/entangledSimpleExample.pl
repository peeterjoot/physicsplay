#!/usr/bin/perl

my %h1 = 
(
	'0' => '1',
	'1' => '2'
) ;

my %h2 = 
(
	'0' => '+',
	'1' => '-'
) ;

for ( my $a = 0 ; $a < 2 ; $a++ )
{
	for ( my $b = 0 ; $b < 2 ; $b++ )
	{
		for ( my $c = 0 ; $c < 2 ; $c++ )
		{
			for ( my $d = 0 ; $d < 2 ; $d++ )
			{
				my ($A, $B, $C, $D) = ($h1{$a}, $h1{$b}, $h2{$c}, $h2{$d}) ;

				print "+ a_{$A$B$C$D} \\ket{$A}\\bra{$B} \\otimes \\ket{$C}\\bra{$D}\n" ;
			}
		}
	}
}

for ( my $a = 0 ; $a < 2 ; $a++ )
{
	for ( my $b = 0 ; $b < 2 ; $b++ )
	{
		my ($A, $B) = ($h1{$a}, $h2{$b}) ;

		print "+ h_{$A$B} \\ket{$A} \\otimes \\ket{$B}\n" ;
	}
}

for ( my $a = 0 ; $a < 2 ; $a++ )
{
	for ( my $b = 0 ; $b < 2 ; $b++ )
	{
		my ($A, $B) = ($h1{$a}, $h2{$b}) ;

		print "+ a_{$A} b_{$B} \\ket{$A} \\otimes \\ket{$B}\n" ;
	}
}
