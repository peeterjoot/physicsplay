using PyPlot

include("spring.jl") ;

masses = 0.1:0.1:0.5 ;
#colors = [ "purple", "green", "red", "blue", "black" ] ;
e = 0.005 ;
n = 1000 ;
xrange = collect( e:d/n:d-e ) ;
plotabs = true ;
for i in 1:length(masses)
   m = masses[i] ;
   y = E_s( xrange ) + E_w( m, xrange) ;

   if ( plotabs )
      #plot( xrange, log( y + 2 ), color=colors[i] ) ;
      plot( xrange, log( y + 2 ), label="m = $m" ) ;
   else
      xd = xrange[1:end-1] + d/n/2 ;
      plot( xd, diff( y ), color=colors[i] ) ;
   end
end

if ( plotabs )
   xlabel("x")
   ylabel(L"$\ln E_{tot}$")
   title(L"Nonlinear spring, $\ln(E_{tot} +2)$ vs position.")
   legend() ;
   grid("on")

   savefig("LogEnergyVsPositionFig1.pdf")
end
