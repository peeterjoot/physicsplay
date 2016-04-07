using PyPlot

function plotit( )
   figure() ;
   csvfile = "minTimeVsParallelism.csv" ;

   pdffile = "minTimeVsParallelismFig1.pdf" ;
   csv = readdlm( csvfile, ',' ) ;

   plot( csv[:, 1], csv[:, 2] ) ;

   xlabel( "threads" ) ;
   ylabel( "time" ) ;
   grid( "on" ) ;
   legend( loc="upper left" ) ;

   savefig( pdffile ) ;

end

plotit( ) ;
