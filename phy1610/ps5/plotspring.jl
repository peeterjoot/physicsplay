using PyPlot

#In these expression, the parameters are as follows:
a = 1 ; #J (energy scale)
b = 0.1 ; #m (length scale)
c = 100 ; #N/m (spring constant)
d = 0.5 ; #m(maximum spring extension)
f = 2500 ; #(stiffness at maximum extension)
g = 9.8 ; #m/s^2 (gravitational accelleration).

function E_s(x)
   (a * b) ./ x + (a * d^2/f) ./ ( (d - x).^2 ) - a * exp( -(c/2/a) * (x - b).^2 )  
end

function E_w(m, x)
   - m * g .* x
end

m = 0.1 ;
e = 0.01 ;
xrange = collect( e:d/1000:d-e ) ;
y = E_s(xrange) + E_w( m, xrange) ;

xsz = length(xrange) ;
xd = xrange[1:xsz-1]
di = Array( Float64, xsz ) ;    
# there's probably a function for adjacent differences, but can't look it 
# up while offline:
for i in 1:xsz-1
   di[i] = y[i+1]-y[i]
end

plot( xrange, y, color="red", linewidth=2.0 ) 
#plot( xrange, di, color="blue", linewidth=2.0 ) 
