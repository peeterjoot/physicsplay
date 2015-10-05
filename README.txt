Peeter Joot's geometric algebra biased math and physics latex source.

#-------------------------------------------------------
# grabbing a copy of the tree
#

git clone git@github.com:peeterjoot/physicsplay.git ~/physicsplay
cd ~/physicsplay
for i in getopt mathematica figures matlab clang julia ; do
   git submodule update --init $i
   (cd $i && git checkout master)
done

#-------------------------------------------------------

Some directories in this repository:

bin/

   Some scripts.

notes/blogit/

   Various things in unfinished states.

notes/atomic/

   Some informal papers on atomic operations and memory barriers.

notes/gabook/

   'Exploring physics with Geometric Algebra' -- a too large collection of Geometric Algebra related math and physics.

notes/miscphysics/

   A collection of mostly non-Geometric Algebra related math physics notes (since my GA stuff is collected separately).

notes/otherbook/

   Junky incomplete and wrong Physics and Math Play or Just Unsorted.

notes/papers/
   http://arxiv.org/abs/1104.4829 -- Change of basis and Gram-Schmidt orthonormalization in special relativity
   relwave.tex -- expanding on Pauli's derivation of Schrodinger's equation from the Klein-Gordon equation.

notes/classicalmechanics/

   Personal study notes on Lagrangians, and Hamiltonians (Reading of Goldstein, ... ).
   These are currently part of the posted gabook.pdf, but I've pulled them into this collection because
   gabook is too big.

   There are also some classical mechanics notes and problems from auditing a small subset of
   'Advanced Classical Mechanics', taught by Prof. Erich Poppitz.
   I only ended up doing the first problem set from that course, although I still indend to go back and
   revisit the rest to ensure I've got these basics down.

notes/phy450/

   Class notes and problems from 'Relativistic Electrodynamics', taught by Prof. Erich Poppitz.

notes/phy454/

  Class notes and problems from 'Continuum Mechanics', taught by Prof. Kausik S. Das.

notes/phy356/

  Class notes and problems from 'Quantum I', taught by Prof. Vatche Deyirmenjian.

notes/phy456/

  Class notes and problems from 'Quantum II', taught by Prof. John Sipe.

notes/phy485/

  Class notes and problems from 'Advanced Classical Optics', taught by Prof. Joseph Thywissen.

notes/phy452/

  Class notes and problems from 'Basic Statistical Mechanics', taught by Prof. Arun Paramekanti.

notes/phy487/

  Class notes and problems from 'Condensed Matter Physics', taught by Prof. Stephen Julian.

notes/ece1254/

  Class notes and problems from 'Modeling of Multiphysics Systems', taught by Prof. P. Triverio.

notes/ece1229/

  Class notes and problems from 'Advanced Antenna Theory', taught by Prof. G.V. Eleftheriades.

notes/phy1520/

  Class notes and problems from 'Graduate Quantum Mechanics', taught by Prof. Arun Paramekanti. (in progress)

notes/resume/

   A hack job of a resume produced for a google head hunter, since I was curious what sort of job he was offering
   but didn't have any expectation I'd accept.

   Later used for my M.Eng master application (added writing notes, removed the "other-projects" notes that google wanted).

sym/

   A C++ geometric algebra symbolic calculator using the 'gasandbox' libraries.

cpuinfo/

   inline assembly test for powerpc mfpvr instruction.
   test program that reads AT_PLATFORM from the ELF binary object header.

env/

   some aliases, and .vimrc, sort of stuff.

studentNumberGrep/

   a little perl regex sample

tmcache/

   prototype code to attempt to avoid non-signal safe function localtime_r(), which can be desirable
   to use in a signal handler.

notes/peterlue/
  
   A sample simple latex file for Peter.

notes/gamma-matrix

   Some C++ gamma matrix related code.  Forget exactly what it did.  Uses boost::ublas.

notes/dekker
   
   a dekker's algorithm related "paper" posted to my blog, discussing memory ordering.

del2xml/del2xml

   A script to take .csv formatted stuff and massage it into the xml format that rocketshuttle likes.
