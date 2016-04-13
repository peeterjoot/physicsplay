
params="waveparamsPs10.txt"
#params="waveparams.txt"

rm -f dataFilename*out
mpirun -n 1 ./wave1d $params >/dev/null
cat dataFilename_0.out | grep -v '#' | sort -k1 -n -t' ' -k2 -n -t' ' > aggregate.out.1

# start seeing differences with mpi-size == 4:
for i in 4 ; do
#for i in 2 3 4 ; do
#for i in 3 4 6 ; do
#for i in 2 5 10 ; do
   rm -f dataFilename*out
   mpirun -n $i ./wave1d  $params >/dev/null
   cat dataFilename*out | grep -v '#' | sort -k1 -n -t' ' -k2 -n -t' ' > aggregate.out.$i

   echo "# diff -up aggregate.out.1 aggregate.out.$i"
   diff -up aggregate.out.1 aggregate.out.$i
done
