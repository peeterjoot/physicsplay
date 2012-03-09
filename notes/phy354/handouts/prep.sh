f="Advanced_Classical_Mechanics.in"
mv "Advanced Classical Mechanics.htm" "Advanced_Classical_Mechanics.in" 2>/dev/null
./grabUrls.pl PHY354_files http://www.physics.utoronto.ca/~poppitz/epoppitz/ < $f 
#my $files = '
#perl -p xx.pl < $f > Advanced_Classical_Mechanics.htm
