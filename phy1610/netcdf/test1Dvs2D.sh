./writefile  ; ncdump first.netCDF.nc > d.1D.1
./writefile --nrec=2 ; ncdump first.netCDF.nc > d.1D.2
./writefile --nrec=3 ; ncdump first.netCDF.nc > d.1D.3

./writefile2D  ; ncdump first.netCDF.nc > d.2D.1
./writefile2D --nrec=2 ; ncdump first.netCDF.nc > d.2D.2
./writefile2D --nrec=3 ; ncdump first.netCDF.nc > d.2D.3

for i in 1 2 3 ; do 
   diff -up d.1D.$i d.2D.$i
done
