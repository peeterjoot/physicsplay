cp gmblk.C.in tt.C
H=`(cd $HOME && /bin/pwd)`
#CLANGBINDIR=$H/clang/debug48rt/bin
CLANGBINDIR=$H/clang/optimized48rt/bin
#make $CLANGBINDIR/RenameMethod && gdb $CLANGBINDIR/RenameMethod 
make $CLANGBINDIR/RenameMethod && $CLANGBINDIR/RenameMethod tt.C
diff -u gmblk.C.in tt.C
