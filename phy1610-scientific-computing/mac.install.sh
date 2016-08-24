/usr/bin/ruby -e "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/master/install)"

for i in binutils boost fftw gcc gdb gmp gsl hdf5 homebrew/science/openblas homebrew/science/scalapack netcdf open-mpi openssl pgplot ; do
   brew install $i
done
