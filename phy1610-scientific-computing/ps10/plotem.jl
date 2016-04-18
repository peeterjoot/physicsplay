using PyPlot

function plotit( )
   figure() ;
   csvfile = "minTimeVsParallelism.csv" ;

   pdffile = "minTimeVsParallelismFig1.pdf" ;
   csv = readdlm( csvfile, ',' ) ;

   plot( csv[:, 1], csv[:, 2] ) ;

   xlabel( "mpi tasks" ) ;
   ylabel( "time (sec)" ) ;
   grid( "on" ) ;

   savefig( pdffile ) ;

end

plotit( ) ;
