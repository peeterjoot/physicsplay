where=llvm
#where=llvmopt
#what=trunk

#svn ls http://llvm.org/svn/llvm-project/llvm/tags/
what=tags/RELEASE_350/final

#Checkout LLVM:
#Change directory to where you want the llvm directory placed.
echo svn co http://llvm.org/svn/llvm-project/llvm/$what $where

#Checkout Clang:
echo cd $where/tools
echo svn co http://llvm.org/svn/llvm-project/cfe/$what clang
echo cd ../..

#Checkout extra Clang Tools: (optional)
echo cd $where/tools/clang/tools
echo svn co http://llvm.org/svn/llvm-project/clang-tools-extra/$what extra
echo cd ../../../..

#Checkout Compiler-RT:
echo cd $where/projects
echo svn co http://llvm.org/svn/llvm-project/compiler-rt/$what compiler-rt
echo cd ../..

#Build LLVM and Clang:
#mkdir build (for building without polluting the source dir)
#cd build
#../$where/configure
#../$where/configure --enable-optimized
#make
#This builds both LLVM and Clang for debug mode.
#Note: For subsequent Clang development, you can just do make at the clang directory level.
#It is also possible to use CMake instead of the makefiles. With CMake it is also possible to generate project files for several IDEs: Eclipse CDT4, CodeBlocks, Qt-Creator (use the CodeBlocks generator), KDevelop3.
#If you intend to work on Clang C++ support, you may need to tell it how to find your C++ standard library headers. In general, Clang will detect the best version of libstdc++ headers available and use them - it will look both for system installations of libstdc++ as well as installations adjacent to Clang itself. If your configuration fits neither of these scenarios, you can use the --with-gcc-toolchain configure option to tell Clang where the gcc containing the desired libstdc++ is installed.
#Try it out (assuming you add $where/Debug+Asserts/bin to your path):
#clang --help
#clang file.c -fsyntax-only (check for correctness)
#clang file.c -S -emit-llvm -o - (print out unoptimized llvm code)
#clang file.c -S -emit-llvm -o - -O3
#clang file.c -S -O3 -o - (output native machine code)
