using PyPlot

run( `./springmodel -f x.csv` ) ;
csv = readdlm( "x.csv", ' ' ) ;
run( `rm -f x.csv` ) ;
csvx = csv[ 2:end-1, 1 ] ;
csvy = csv[ 2:end-1, 2 ] ;

plot( csvx, csvy, color="blue", linewidth=2.0 ) 

xlabel("Mass")
ylabel("Position of minimum total energy")
title("Nonlinear spring.  Position of min E_tot for masses in [0,0.5] range.")
grid("on")

savefig("massextensionFig1.pdf")
