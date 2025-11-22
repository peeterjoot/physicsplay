
set -x

rm -f *.pcm *.o try gcm.cache

# 1. Build the standard library module once (~45–90 seconds)
clang++ -std=c++23 -stdlib=libc++ \
        -Wno-reserved-module-identifier \
        --precompile /usr/share/libc++/v1/std.cppm \
        -o std.pcm

# 2. Build your own module interface (stuff)
#     This is the critical one — it MUST see the std module by name
clang++ -std=c++23 -stdlib=libc++ \
        -fmodule-file=std=std.pcm \
        -c -x c++-module stuff.cc \
        -o stuff.pcm
#        -fmodules-validate-once-per-build-unit \

# 3. Compile the importer (try.cc)
clang++ -std=c++23 -stdlib=libc++ \
        -fmodule-file=std=std.pcm \
        -fmodule-file=stuff=stuff.pcm \
        -c try.cc -o try.o

# 4. Link (Clang 20 does NOT need the .pcm files on the link line)
clang++ -std=c++23 -stdlib=libc++ try.o -o try
