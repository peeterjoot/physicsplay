#!/usr/bin/perl -p -i

BEGIN
{

$n = $ENV{START} ;
$n = 10 unless ( defined $n ) ;

}

if ( s/:n} *$/:$n}/ )
{
   $n += 20 ;
}
