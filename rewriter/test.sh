#echo // asample1.cpp
./classvisitor -Iinc -Dfoodef -Dbardef=2 asample1.cpp
#echo 
#echo 
#echo 
#
#echo // asample2.cpp
#./classvisitor asample2.cpp
#echo 
#echo 
#echo 
#
#echo // asample3.cpp
#./globalvisitor asample3.cpp
#echo 
#echo 
#echo 
#
#echo // asample4.cpp
#./globalvisitor asample4.cpp
#echo 
#echo 
#echo 
#
#echo // asample5.cpp
#./classvisitor asample5.cpp
#echo 
#echo 
#./classvisitor -I./inc asample1.cpp
#./classvisitor -I`pwd`/inc asample1.cpp
#echo // asample5.cpp
#cp asample5.cpp retest.cpp
#./rewriter retest.cpp
#diff -up asample5.cpp retest.cpp
#echo 
#echo 
