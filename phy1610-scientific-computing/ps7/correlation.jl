
# same data as x.rat, y.rat, used in boost test driver test.cc
x = [ 0, 0.0999999, 0.2, 0.3, 0.4, 0.5, 0.6, 0.699999, 0.799999, 0.899999, 0.999999, 1.1, 1.2, 1.3, 1.4 ] ;
y = [ 1, 1.0999999, 1.2, 1.3, 1.4, 1.5, 1.6, 1.699999, 1.799999, 1.899999, 1.999999, 2.1, 2.2, 2.3, 2.4 ] ;

xx = dot( x, x ) ;
xy = dot( x, y ) ;
yy = dot( y, y ) ;

xy/sqrt( xx * yy )