# http://stackoverflow.com/questions/16408893/gnu-ld-gdb-separate-debug-files-how-to-produce-the-debug-file-when-theres-too

CXXFLAGS += -g
TARGETS := uWithBuildId uWithDebugLink

all : $(TARGETS)

uWithBuildId : u.o
	$(CXX) -o $@ -Wl,--build-id $<
	copyDebugAndStrip $@

uWithDebugLink : u.o
	$(CXX) -o $@ $<
	objcopy --only-keep-debug $@ $@.debug
	objcopy --add-gnu-debuglink=$@.debug $@
	strip -g $@

clean :
	rm -rf $(TARGETS) *.debug .build-id *.o
