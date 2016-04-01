using PyPlot

function plotit( )
   figure() ;
   csvfile = "part2pivotdata.csv" ;
   pdffile = "part2pivotdata.pdf" ;

   if ( !isfile( pdffile ) )
      csv = readdlm( csvfile, ',' ) ;

      plot( csv[:, 1], csv[:, 2], label ="outtime=1" ) ;
      plot( csv[:, 1], csv[:, 3], label ="outtime=10" ) ;
      plot( csv[:, 1], csv[:, 4], label ="outtime=20" ) ;

      xlabel( "threads" ) ;
      ylabel( "time" ) ;
      grid( "on" ) ;
      legend( loc="upper right" ) ;

      savefig( pdffile ) ;
   end
end

plotit( ) ;
