use English( qw(OSNAME) ) ;

# match either MSWin32 or cygwin (and perhaps MSWin64?)
my $amWindows = ( $OSNAME =~ /win/i ) ? 1 : 0 ;

print "$amWindows\n" ;
