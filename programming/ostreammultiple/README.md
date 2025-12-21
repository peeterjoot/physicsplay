## What's the point of this?

Just looking to see if current versiosn of gcc or clang merge back to back printfs, or c++ ostream equivalents, in circumstances that appear viable for that optimization.  I'm pretty sure that all of xlC, icc, and MSVC all used to do this.

'objdump -d' on the outputs shows that there is a trivial conversion of printf w/ \n into puts, but neither gcc nor clang currently tries to do anything more.
