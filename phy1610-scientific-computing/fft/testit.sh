./inplace --infile=inplace.in --outfile=inplace.out
./twoarrays --infile=twoarrays.in --outfile=twoarrays.out

diff -up inplace.in twoarrays.in
diff -up inplace.out twoarrays.out
