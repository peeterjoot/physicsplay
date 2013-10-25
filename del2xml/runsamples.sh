./del2xml < sample.csv > sample.xml
./del2xml -dollar < sample2.csv > sample2.xml
./del2xml -del Z < sample3.csv > sample3.xml

diff *2.xml *3.xml > all.diff
diff sample.xml *3.xml >> all.diff
echo 'test.  wc should be zero'
wc -l all.diff
