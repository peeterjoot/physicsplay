# You can do the read-only Git clone of LLVM via:
(git clone http://llvm.org/git/llvm.git)



# If you want to check out clang too, run:
(cd llvm/tools && git clone http://llvm.org/git/clang.git)



# If you want to check out compiler-rt (required to build the sanitizers), run:
(cd llvm/projects && git clone http://llvm.org/git/compiler-rt.git)


# If you want to check out libomp (required for OpenMP support), run:
(cd llvm/projects && git clone http://llvm.org/git/openmp.git)


# If you want to check out libcxx and libcxxabi (optional), run:
#cd llvm/projects
#git clone http://llvm.org/git/libcxx.git
#git clone http://llvm.org/git/libcxxabi.git


# If you want to check out the Test Suite Source Code (optional), run:
#(cd llvm/projects && git clone http://llvm.org/git/test-suite.git)


# Since the upstream repository is in Subversion, you should use git pull --rebase instead of git pull to avoid generating a non-linear history in your clone. To configure git pull to pass --rebase by default on the master branch, run the following command:
#git config branch.master.rebase true
