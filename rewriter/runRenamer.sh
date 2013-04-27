#cp gmblk.C.in tt.C
H=`(cd $HOME && /bin/pwd)`

#CLANGBINDIR=$H/clang/debug48rt/bin
CLANGBINDIR=$H/clang/optimized48rt/bin

#i=gblkToGmblk
#make $CLANGBINDIR/$i && $CLANGBINDIR/$i tt.C
#diff -u gmblk.C.in tt.C

cp tt.C uu.C
i=stripGmblkVoidPPcast
make $CLANGBINDIR/$i && $CLANGBINDIR/$i uu.C
#make $CLANGBINDIR/$i && gdb $CLANGBINDIR/$i #uu.C

