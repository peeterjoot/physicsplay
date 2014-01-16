git rev-list --objects --all | sort -k 2 > allfileshas.txt
git rev-list --objects --all | sort -k 2 | grep ' ' | cut -f 2 -d' '  | uniq > uniq.txt

git gc && git verify-pack -v .git/objects/pack/pack-*.idx | egrep "^\w+ blob\W+[0-9]+ [0-9]+ [0-9]+$" | sort -k 3 -n -r > bigobjects.txt

for SHA in `cut -f 1 -d\  < bigobjects.txt`; do
echo $(grep $SHA bigobjects.txt) $(grep $SHA allfileshas.txt) | awk '{print $1,$3,$7}' >> bigtosmall.txt
done;

cut -f3 -d' ' bigtosmall.txt  > l

for i in `cat l` ; do test -e $i || echo $i ; done | tee q

grep -Ff q bigtosmall.txt > gitcleaning/bigtosmall.missing.txt
rm allfileshas.txt uniq.txt bigtosmall.txt l q

cd gitcleaning

cut -f3 -d' ' bigtosmall.missing.txt > bigtosmall.missing.txt.f
