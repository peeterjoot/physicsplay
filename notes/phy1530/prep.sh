f="Graduate_Fluid_Mechanics.in"
mv "Graduate Fluid Mechanics.htm" "Graduate_Fluid_Mechanics.in" 2>/dev/null
perl ~/bin/grabUrls.pl PHY1530_files http://www.physics.utoronto.ca/~poppitz/epoppitz/ $f 
perl -p xx.pl < $f > Graduate_Fluid_Mechanics.htm
