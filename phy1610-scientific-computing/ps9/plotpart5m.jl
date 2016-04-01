using PyPlot

function plotit( )
   figure() ;
   csvfile = "part5pivotdata.csv" ;
   pdffile = "ps9part5pivotdataMultiFileFig3.pdf" ;

   csv = readdlm( csvfile, ',' ) ;

   plot( csv[1:5, 2], csv[1:5, 3], label ="outtime=0.1" ) ;
   plot( csv[1:5, 2], csv[1:5, 4], label ="outtime=1" ) ;
   plot( csv[1:5, 2], csv[1:5, 5], label ="outtime=10" ) ;
   plot( csv[1:5, 2], csv[1:5, 6], label ="outtime=20" ) ;
   plot( csv[1:5, 2], csv[1:5, 7], label ="outtime=33" ) ;

   xlabel( "threads" ) ;
   ylabel( "time" ) ;
   grid( "on" ) ;
   legend( loc="upper left" ) ;

   savefig( pdffile ) ;


end

plotit( ) ;
