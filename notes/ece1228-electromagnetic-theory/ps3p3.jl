#!/usr/local/bin/julia

n = [3,2,1] ;
E1 = [2,0,5] ;
e1 = 3 ;

nsq = dot( n, n ) ;
nE1 = dot( n, E1 ) ;

# result:
E2 = E1 + (e1-1)n * nE1/nsq ;

# check:

normal = dot( n, e1 * E1 ) - dot( n, E2 ) ;
tangential = cross( n, E1 ) - cross( n, E2 ) ;

print( "$E2\n" ) ;
print( "$normal\n" ) ;
print( "$tangential\n" ) ;

manual = [47,22,46]/7 - E2 ;
print( "$manual\n" ) ;
