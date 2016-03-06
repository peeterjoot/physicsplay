using PyPlot

function plotit( filebase )
   figure() ;
   csvfile = "$filebase.csv" ;

   if ( !isfile( csvfile ) )
      run( `./ratToCsv "--filename=$filebase.rat"` ) ;
   end

   pdffile = "$filebase.pdf" ;
   if ( !isfile( pdffile ) )
      csv = readdlm( csvfile, ',' ) ;

      plot( csv[:, 1], csv[:, 2], label ="real" ) ;
      plot( csv[:, 1], csv[:, 3], label ="imag" ) ;
      complex = csv[:, 2]+ im * csv[:, 3] ;
      plot( csv[:, 1], abs(complex), label ="abs" ) ;

      xlabel( "time" ) ;
      grid( "on" ) ;
      legend( loc="lower left" ) ;

      savefig( pdffile ) ;
   end
end

plotit( "GWprediction" ) ;
plotit( "detection01" ) ;
plotit( "detection16" ) ;
plotit( "detection32" ) ;
