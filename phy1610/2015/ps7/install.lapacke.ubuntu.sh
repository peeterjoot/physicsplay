apt-get install libblas-dev checkinstall
apt-get install libblas-doc checkinstall
apt-get install liblapacke-dev checkinstall

# this hung the first time, and I had to clean up with:
#  dpkg --configure -a
#  dpkg --remove --force-remove-reinstreq liblapack-doc
#
apt-get install liblapack-doc checkinstall

# ended up installing without checkinstall... am not sure if that made the difference.
