#!/usr/bin/perl -n

#
# take a list of files like:
#
#1:IMG_0517.JPG
#2:IMG_0522.JPG
#3:IMG_0523.JPG
# 
# ie: output of:
# ls -ltr | sed 's/.* //' | grep -n ^
#
# and rename in sequence.
#

chomp ;

/(.*?):(IMG_.*)/ or die ;
my ( $n, $f ) = ( $1, $2 ) ;

printf "mv -i $f IMG_%04d.JPG\n", $n ;
