# with waveparamsid.txt::initdebug=1
su=" -u"
for i in 2 3 4 5 6 7 8 9 10 ; do
   rm -f initlog*out
   ./wave1d waveparamsid.txt >/dev/null
   mv initlog0.out x1

   # with high enough contention (i=10) the output gets melded together.
   mpirun -n $i ./wave1d  waveparamsid.txt >/dev/null
   cat initlog*out | sort -k2 -n $su > x2

   echo "diff: size = $i"
   diff -up x1 x2
done
