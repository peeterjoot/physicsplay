
for i in getopt mathematica figures matlab clang julia ; do
   git submodule update --init $i
   (cd $i && git checkout master)
done
