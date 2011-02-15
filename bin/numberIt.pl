#!/usr/bin/perl -p -i

BEGIN
{

$n = 10 ;

}

if ( s/:n} *$/:$n}/ )
{
   $n += 20 ;
}
