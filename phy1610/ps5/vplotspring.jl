using PyPlot

include("spring.jl") ;

masses = [ 0.001, 0.01, 0.05, 0.2, 0.4 ] ;
e1 = 0.075 ;
e2 = 0.02 ;
n = 1000 ;
xrange = collect( e1:d/n:d-e2 ) ;
plotabs = true ;
for i in 1:length(masses)
   m = masses[i] ;
   y = E_s( xrange ) + E_w( m, xrange) ;

   if ( plotabs )
      plot( xrange, y, label="m = $m" ) ;
   else
      xd = xrange[1:end-1] + d/n/2 ;
      plot( xd, diff( y ), color=colors[i] ) ;
   end
end

if ( plotabs )
   xlabel("x")
   ylabel(L"$E_{tot}$")
   title(L"Nonlinear spring, $E_{tot}$ vs position.")
   legend( loc="lower left" ) ;
   grid("on")

   savefig("energyVsPositionFig1.pdf")
end
