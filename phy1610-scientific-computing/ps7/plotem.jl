using PyPlot

function plotit( filebase )
   figure() ;
   csv = readdlm( "$filebase.csv", ',' ) ;

   plot( csv[:, 1], csv[:, 2], label ="real" ) ;
   plot( csv[:, 1], csv[:, 3], label ="imag" ) ;
   complex = csv[:, 2]+ im * csv[:, 3] ;
   plot( csv[:, 1], abs(complex), label ="abs" ) ;

   xlabel("time") ;
   grid("on") ;
   legend( loc="lower left" ) ;

   savefig("$filebase.pdf")
end

plotit( "GWprediction" ) ;
plotit( "detection01" ) ;
