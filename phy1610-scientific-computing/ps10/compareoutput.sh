
params="waveparamsPs10.txt"
#params="waveparams.txt"

rm -f dataFilename*out
mpirun -n 1 ./wave1d $params >/dev/null
mysort="sort -k1,2 -t, -n"
$mysort < dataFilename_0.out > aggregate.out.1

for i in 2 5 10 ; do
   rm -f dataFilename*out
   mpirun -n $i ./wave1d  $params >/dev/null
   cat dataFilename*out | sort -u | $mysort > aggregate.out.$i

   echo "diff: size = $i"
   diff -up aggregate.out.1 aggregate.out.$i
done
