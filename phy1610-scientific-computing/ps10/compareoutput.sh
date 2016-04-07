
#pat="init:"
pat="0:"
for i in 2 ; do
   rm -f dataFilename*out
   ./wave1d waveparams.txt >/dev/null
   grep $pat dataFilename0.out > x1

   # with high enough contention (i=10) the output gets melded together.
   rm -f dataFilename*out
   mpirun -n $i ./wave1d  waveparams.txt >/dev/null
   cat dataFilename*out | grep $pat | sort -k2 -n -u > x2

   echo "diff: size = $i"
   diff -up x1 x2
done
