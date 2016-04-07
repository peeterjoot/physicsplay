
#pat="init:"
pat="0:"

rm -f dataFilename*out
mpirun -n 1 ./wave1d waveparams.txt >/dev/null
grep $pat dataFilename0.out > x1

for i in 2 5 10 ; do
   rm -f dataFilename*out
   mpirun -n $i ./wave1d  waveparams.txt >/dev/null
   cat dataFilename*out | grep $pat | sort -k2 -n -u > x2

   echo "diff: size = $i"
   diff -up x1 x2
done
