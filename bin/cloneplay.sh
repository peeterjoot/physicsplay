
for i in getopt mathematica figures matlab clang julia notes/latex ; do
   git submodule update --init $i
   (cd $i && git checkout master)
done
