#!/usr/bin/perl

for ( my $i = 0 ; $i < 64 ; $i++ )
{
print "
void foo$i( char * b )
{
   int * v = (int *) b ;

   *v = $i ;
}

" ;
}

print "
void foo( char * b )
{
   long a = (long)b & 63 ;

   switch ( a )
   {
" ;

for ( my $i = 0 ; $i < 64 ; $i++ )
{
   print "     case $i : foo$i( b ) ; break ;\n" ;
}

print "
   }
}
" ;
