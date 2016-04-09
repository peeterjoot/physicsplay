for i in 1 2 3 4 5 6 7 8 9 10 ; do
   mpirun -n $i ./writefilep ; ncdump foo.nc > n.$i.out

   diff -up n.1.out n.$i.out
done

rm -f n.*.out
