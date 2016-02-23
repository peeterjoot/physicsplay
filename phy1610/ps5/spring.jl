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


