using PyPlot

function plotit( )
   figure() ;
   csvfile = "part5pivotdata.csv" ;

   pdffile = "ps9part5pivotdataSerialFig4.pdf" ;
   csv = readdlm( csvfile, ',' ) ;

   plot( csv[6:10, 2], csv[6:10, 3], label ="outtime=0.1" ) ;
   plot( csv[6:10, 2], csv[6:10, 4], label ="outtime=1" ) ;
   plot( csv[6:10, 2], csv[6:10, 5], label ="outtime=10" ) ;
   plot( csv[6:10, 2], csv[6:10, 6], label ="outtime=20" ) ;
   plot( csv[6:10, 2], csv[6:10, 7], label ="outtime=33" ) ;

   xlabel( "threads" ) ;
   ylabel( "time" ) ;
   grid( "on" ) ;
   legend( loc="upper left" ) ;

   savefig( pdffile ) ;

end

plotit( ) ;
