my @strings = ( "hi bye", "hello world", "why now", "one two" ) ;

foreach ( @strings )
{
   s/(\S+)\s+(\S+)/'$&' -> '$2 $1'/ ;

   print "$_\n" ;
}
