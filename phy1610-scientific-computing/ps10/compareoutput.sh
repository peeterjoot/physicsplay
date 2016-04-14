
params="waveparamsPs10.txt"
paramsnc="waveparamsPs10nc.txt"
#params="waveparams.txt"

rm -f dataFilename*out
mpirun -n 1 ./wave1d $params >/dev/null
cat dataFilename_0.out | grep -v '#' | sort -k1 -n -t' ' -k2 -n -t' ' > aggregate.out.1

mpirun -n 1 ./wave1d $paramsnc >/dev/null
./readwavenc -f dataFilename.nc > netcdf.out.1 
echo "# diff -up netcdf.out.1 aggregate.out.1"
diff -up netcdf.out.1 aggregate.out.1

# start seeing differences with mpi-size == 4:
for i in 2 3 ; do
#for i in 2 3 4 ; do
#for i in 3 4 6 ; do
#for i in 2 5 10 ; do
   rm -f dataFilename*out
   mpirun -n $i ./wave1d  $params >/dev/null
   cat dataFilename*out | grep -v '#' | sort -k1 -n -t' ' -k2 -n -t' ' > aggregate.out.$i

   echo "# diff -up aggregate.out.1 aggregate.out.$i"
   diff -up aggregate.out.1 aggregate.out.$i

   mpirun -n $i ./wave1d $paramsnc >/dev/null
   ./readwavenc -f dataFilename.nc > netcdf.out.$i
   echo "# diff -up netcdf.out.$i aggregate.out.1"
   diff -up netcdf.out.$i aggregate.out.1
done
