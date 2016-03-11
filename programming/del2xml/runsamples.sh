sed 's/ *, */$/g' < sample.csv > sample2.csv
sed 's/ *, */Z/g' < sample.csv > sample3.csv

./del2xml.perl < sample.csv > sample.xml
./del2xml.perl -dollar < sample2.csv > sample2.xml
./del2xml.perl -del Z < sample3.csv > sample3.xml

diff *2.xml *3.xml > all.diff
diff sample.xml *3.xml >> all.diff
echo 'test.  wc should be zero'
wc -l all.diff

./del2xml.exe < sample.csv > sample.2.xml
./del2xml.exe --delimiter='$' < sample2.csv > sample2.2.xml
./del2xml.exe --delimiter='Z' < sample3.csv > sample3.2.xml
diff -wu *2.2.xml *3.2.xml > all.diff
diff -wu sample.2.xml *3.2.xml >> all.diff
diff -wu sample.xml sample.2.xml >> all.diff
echo 'test2.  should be minimal differences (and only compared to the original perl script)'
wc -l all.diff
