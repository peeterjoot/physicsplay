f="Relativistic_Electrodynamics.in"
mv "Relativistic Electrodynamics.htm" "Relativistic_Electrodynamics.in" 2>/dev/null
perl ~/bin/grabUrls.pl PHY450_files http://www.physics.utoronto.ca/~poppitz/epoppitz/ $f 
perl -p xx.pl < $f > Relativistic_Electrodynamics.htm
