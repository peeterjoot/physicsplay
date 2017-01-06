Peeter Joot's math and physics latex source.

Much of what used to be housed in this repo has now been moved to standalone repositories.

#-------------------------------------------------------
# grabbing a copy of the tree
#

git clone git@github.com:peeterjoot/physicsplay.git ~/physicsplay
cd ~/physicsplay
bin/cloneplay.sh

#-------------------------------------------------------

Some directories in this repository:

archives/

   stuff that is uploaded as-is to peeterjoot.com/archives/

bin/

   Some scripts.

clang/

   submodule.

env/

   some aliases, and .vimrc, sort of stuff.

figures/

   submodule.

getopt/

   submodule.

julia/

   submodule.

mathematica/

   submodule.

matlab/

   submodule.

notes/
   blogit/

      Various things in unfinished states.

   atomic/

      Some informal papers on atomic operations and memory barriers.

   papers/
      http://arxiv.org/abs/1104.4829 -- Change of basis and Gram-Schmidt orthonormalization in special relativity
      relwave.tex -- expanding on Pauli's derivation of Schrodinger's equation from the Klein-Gordon equation.

   ece1229-antenna-project/

     notes for 'Advanced Antenna Theory' project assignment (class taught by Prof. G.V. Eleftheriades.)

   phy2403-qft/
      Problem set 1 (2015?) solutions and some other notes.

   resume/

      A hack job of a resume produced for a google head hunter, since I was curious what sort of job he was offering
      but didn't have any expectation I'd accept.

      Later used for my M.Eng master application (added writing notes, removed the "other-projects" notes that google wanted).

   peterlue/
     
      A sample simple latex file for Peter.

   gamma-matrix/

      Some C++ gamma matrix related code.  Forget exactly what it did.  Uses boost::ublas.

   dekker/
      
      a dekker's algorithm related "paper" posted to my blog, discussing memory ordering.

phy1610-scientific-computing/

   Programming assignents from the UofT (scinet) 2016 Scientific computing course.  Also included is some of the programming assignments from the 2015 course(s) which I did before I officially signed up for this in the 2016 term.

programming/

   Most of the stuff in this dir is simple one-off test programs to try out a specific language feature.

   cpuinfo/

      inline assembly test for powerpc mfpvr instruction.
      test program that reads AT_PLATFORM from the ELF binary object header.
      This method is obsoleted by the new glibc function getauxval() with which we can get at the power hardware version much more easily. (glibc >= 2.16)

   del2xml/

      To take .csv formatted stuff and massage it into the xml format that rocketshuttle likes.  This must have been for Sofia.

   sym/

      A C++ geometric algebra symbolic calculator using the 'gasandbox' libraries.

   tmcache/

      prototype code to attempt to avoid non-signal safe function localtime_r(), which can be desirable
      to use in a signal handler.

   debug/
   gaJuliaFractal/
   gdb_separate_debug_info/
   iter/
   lambda/
   opengl/
   random/
   regex/
   shellcode/
   strcpyOverlapped/
   sym2/

#-------------------------------------------------------

BUGS that prevent 'make' from being successful without handholding:

   - The eps -> pdf rules aren't right.  Have to build in notes/blogit/ before any other notes/*/ dir.

