using PyPlot

run(`./springmodel -m 0.1 -f x.csv`) ;
a = readdlm("x.csv", ',') ;

plot( a[:,1], a[:,2], color="blue", linewidth=2.0 ) 
