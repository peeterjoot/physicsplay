using PyPlot

include("spring.jl") ;

masses = [ 0.001, 0.01, 0.05, 0.2, 0.4 ] ;
e1 = 0.075 ;
e2 = 0.02 ;
n = 1000 ;
xrange = collect( e1:d/n:d-e2 ) ;

for plotabs in 0:2
   figure() ;

   for i in 1:length(masses)
      m = masses[i] ;
      y = E_s( xrange ) + E_w( m, xrange) ;

      if ( 0 == plotabs )
         plot( xrange, y, label="m = $m" ) ;
      else
         xd = xrange[1:end-1] + d/n/2 ;
         dy = diff( y ) ;
         if ( plotabs == 1 )
            plot( xd, dy, label="m = $m" ) ;
         else
            plot( xd, sign(dy) + i/10, label="m = $m" ) ;
         end
      end
   end

   xlabel("x")
   grid("on")

   if ( 0 == plotabs )
      ylabel(L"$E_{tot}$")
      title(L"Nonlinear spring, $E_{tot}$ vs position.")
      legend( loc="lower left" ) ;

      savefig("energyVsPositionFig1.pdf")
   else
      if ( 1 == plotabs )
         ylabel(L"$d E_{tot}$")
         title(L"Nonlinear spring, $d E_{tot}$ vs position.")
         legend( loc="lower right" ) ;

         savefig("DeltaEnergyVsPositionFig1.pdf")
      else
         ylabel(L"$sgn(d E_{tot})$")
         title(L"Nonlinear spring, $sgn(d E_{tot})$ vs position.")
         legend( loc="lower right" ) ;

         savefig("SignDeltaEnergyVsPositionFig1.pdf")
      end
   end
end
