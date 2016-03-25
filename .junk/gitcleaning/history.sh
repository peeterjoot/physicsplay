# chicken-and-egg: will want to remove some of the stuff in this dir too after running it.

#git rev-list --objects --all | sort -k 2 > allfileshas.txt
##git rev-list --objects --all | sort -k 2 | cut -f 2 -d' '  | uniq > uniq.txt
#git rev-list --objects --all | sort -k 2 | grep ' ' | cut -f 2 -d' '  | uniq > uniq.txt

#git gc && git verify-pack -v .git/objects/pack/pack-*.idx | egrep "^\w+ blob\W+[0-9]+ [0-9]+ [0-9]+$" | sort -k 3 -n -r > bigobjects.txt

#for SHA in `cut -f 1 -d\  < bigobjects.txt`; do
#echo $(grep $SHA bigobjects.txt) $(grep $SHA allfileshas.txt) | awk '{print $1,$3,$7}' >> bigtosmall.txt
#done;

#git filter-branch --prune-empty --index-filter 'git rm -rf --cached --ignore-unmatch notes/phy487/mathematica/ps8e.nb' --tag-name-filter 'cat -- --all'
#git filter-branch --index-filter 'git rm --cached notes/phy487/mathematica/ps8e.nb' HEAD

#git filter-branch --force --index-filter 'git rm --cached --ignore-unmatch notes/phy487/mathematica/ps8e.nb' --prune-empty --tag-name-filter cat -- --all

# http://stackoverflow.com/questions/5563564/completely-remove-files-from-git-repo-and-remote-on-github?lq=1
#git filter-branch --index-filter 'git rm -r --cached --ignore-unmatch notes/phy487/mathematica/ps8e.nb' HEAD
#rm -rf .git/refs/original/ && git reflog expire --all &&  git gc --aggressive --prune

#export file=notes/algebra/dot_linearity_big.png
#git checkout $(git rev-list -n 1 HEAD -- "$file")^ -- "$file"
#git commit -a

#git filter-branch --index-filter 'git rm -r --cached --ignore-unmatch notes/algebra/dot_linearity_big.png' HEAD
#rm -rf .git/refs/original/ && git reflog expire --all &&  git gc --aggressive --prune

#for i in notes/phy487/mathematica/3dDensitySample.nb ; do
for i in `cat gitcleaning/bigtosmall.missing.txt.f` ; do
   git filter-branch --index-filter "git rm -r --cached --ignore-unmatch $i" HEAD && rm -rf .git/refs/original/ && git reflog expire --all && git gc --aggressive --prune
done
