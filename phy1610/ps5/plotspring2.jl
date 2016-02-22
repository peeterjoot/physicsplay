using PyPlot

run(`make x.csv`) ;
a = readdlm("x.csv", ',') ;

plot( a[:,1], a[:,2], color="blue", linewidth=2.0 ) 
