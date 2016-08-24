Peeter Joot's geometric algebra biased math and physics latex source.

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

   gabookI/

      The first part of 'Exploring physics with Geometric Algebra' -- a too large collection of Geometric Algebra related math and physics.  Book I has lots of geometry and some basic physics:

         Basics and Geometry
         Projection
         Rotation
         Calculus
         General Physics

   gabookII/

      The second part of 'Exploring physics with Geometric Algebra' -- a too large collection of Geometric Algebra related math and physics.  Book II contains stuff about

         Relativity
         Electrodynamics
         Lorentz Force
         Electrodynamics Stress Energy
         Quantum Mechanics
         Fourier treatments

   miscphysics/

      A collection of mostly non-Geometric Algebra related math physics notes (since my GA stuff is collected separately).

   otherbook/

      Junky incomplete and wrong Physics and Math Play or Just Unsorted.

   papers/
      http://arxiv.org/abs/1104.4829 -- Change of basis and Gram-Schmidt orthonormalization in special relativity
      relwave.tex -- expanding on Pauli's derivation of Schrodinger's equation from the Klein-Gordon equation.

   classicalmechanics/

      Personal study notes on Lagrangians, and Hamiltonians (Reading of Goldstein, ... ).
      These are currently part of the posted gabook.pdf, but I've pulled them into this collection because
      gabook is too big.

      There are also some classical mechanics notes and problems from auditing a small subset of
      'Advanced Classical Mechanics', taught by Prof. Erich Poppitz.
      I only ended up doing the first problem set from that course, although I still indend to go back and
      revisit the rest to ensure I've got these basics down.

   phy450-relativisticEandM/

      Class notes and problems from 'Relativistic Electrodynamics', taught by Prof. Erich Poppitz.

   phy454-continuumechanics/

     Class notes and problems from 'Continuum Mechanics', taught by Prof. Kausik S. Das.

   phy356-qmI/

     Class notes and problems from 'Quantum I', taught by Prof. Vatche Deyirmenjian.

   phy456-qmII/

     Class notes and problems from 'Quantum II', taught by Prof. John Sipe.

   phy485-optics/

     Class notes and problems from 'Advanced Classical Optics', taught by Prof. Joseph Thywissen.

   phy452-basicstatmech/

     Class notes and problems from 'Basic Statistical Mechanics', taught by Prof. Arun Paramekanti.

   phy487-qmsolids/

     Class notes and problems from 'Condensed Matter Physics', taught by Prof. Stephen Julian.

   ece1254-multiphysics/

     Class notes and problems from 'Modeling of Multiphysics Systems', taught by Prof. P. Triverio.

   ece1229-antenna/

     Class notes and problems from 'Advanced Antenna Theory', taught by Prof. G.V. Eleftheriades.

   phy1520-quantum/

     Class notes and problems from 'Graduate Quantum Mechanics', taught by Prof. Arun Paramekanti. (in progress)

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

