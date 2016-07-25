my @strings = ( "hi bye", "helloworld", "why now", "onetwo" ) ;

foreach ( @strings )
{
   if ( s/(\S+)\s+(\S+)/$2 $1/ )
   {
      print "$_\n" ;
   }
}  
