./wave1dorig ./waveparams.txt > out0
./wave1d ./waveparams.txt > out1
diff -up --ignore-blank-lines out0 out1
