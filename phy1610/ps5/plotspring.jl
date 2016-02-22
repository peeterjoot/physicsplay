using PyPlot
#using PyCall
#@pyimport matplotlib.pyplot as plt ;

#In these expression, the parameters are as follows:
a = 1 ; #J (energy scale)
b = 0.1 ; #m (length scale)
c = 100 ; #N/m (spring constant)
d = 0.5 ; #m(maximum spring extension)
f = 2500 ; #(stiffness at maximum extension)
g = 9.8 ; #m/s^2 (gravitational accelleration).
c1 = a * b ;
c2 = a * d^2/f ;
c3 = -(c/2/a) ;

function E_s(x)
   c1 ./ x + c2 ./ ( (d - x).^2 ) - a * exp( c3 * (x - b).^2 )  
end

function E_w(m, x)
   - m * g .* x
end

m = 0.1 ;
e = 0.01 ;
n = 1000 ;
xrange = collect( e:d/n:d-e ) ;
y = E_s( xrange ) + E_w( m, xrange) ;

run( `./springmodel -m $m -f x.csv -n $n` ) ;
csv = readdlm( "x.csv", ',' ) ;
run( `rm -f x.csv` ) ;
csvx = csv[ :, 1 ] ;
csvy = csv[ :, 2 ] ;

if ( true )
   #plt.close( plt.gcf() ) ;
   plot( xrange, y, color="red", linewidth=2.0 ) 
   plot( csvx, csvy, color="blue", linewidth=2.0 ) 
   #plt.show() ;
else
   xlen = length( xrange ) ;
   clen = length( csvx ) ;
   xd = xrange[1:xlen-1] + d/n/2 ;
   xc = csvx[1:clen-1] + d/n/2 ;
   
   plot( xc, diff( csvy ), color="red", linewidth=2.0 ) 
   plot( xd, diff( y ), color="blue", linewidth=2.0 ) 
end
