using PyPlot

function plotit( filebase )
   figure() ;

   pdffile = "$filebase.pdf" ;
   if ( !isfile( pdffile ) )
      csvfile = "$filebase.txt" ;

      csv = readdlm( csvfile, ' ' ) ;
      trange = collect(0:length(csv)-1) ./ 10.0 ;
      plot( trange, csv )

      xlabel( "time" ) ;
      ylabel( "power" ) ;
      grid( "on" ) ;
      #legend( loc="lower left" ) ;

      savefig( pdffile ) ;
   end
end

#plotit( "GWpredictionFFTPower" ) ;
plotit( "detection01Power" ) ;
