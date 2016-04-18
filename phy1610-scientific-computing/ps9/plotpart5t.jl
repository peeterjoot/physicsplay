using PyPlot

function plotit( )
   figure() ;
   csvfile = "part5pivotdata.csv" ;

   pdffile = "ps9part5pivotdataThreadedFig5.pdf" ;
   csv = readdlm( csvfile, ',' ) ;

   plot( csv[11:15, 2], csv[11:15, 3], label ="outtime=0.1" ) ;
   plot( csv[11:15, 2], csv[11:15, 4], label ="outtime=1" ) ;
   plot( csv[11:15, 2], csv[11:15, 5], label ="outtime=10" ) ;
   plot( csv[11:15, 2], csv[11:15, 6], label ="outtime=20" ) ;
   plot( csv[11:15, 2], csv[11:15, 7], label ="outtime=33" ) ;

   xlabel( "threads" ) ;
   ylabel( "time" ) ;
   grid( "on" ) ;
   legend( loc="upper left" ) ;

   savefig( pdffile ) ;

end

plotit( ) ;
