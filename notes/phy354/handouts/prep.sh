f="Advanced_Classical_Mechanics.in"
mv "Advanced Classical Mechanics.htm" "Advanced_Classical_Mechanics.in" 2>/dev/null
perl ~/bin/grabUrls.pl PHY354_files http://www.physics.utoronto.ca/~poppitz/epoppitz/ $f 
perl -p xx.pl < $f > Advanced_Classical_Mechanics.htm
