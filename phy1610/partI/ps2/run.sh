./wave1dorig ./waveparams.txt > out0
./wave1d ./waveparams.txt > out1
diff -up out0 out1
