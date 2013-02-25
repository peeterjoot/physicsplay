#!/usr/bin/perl

my $CXX = $ARGV[0] ;
die if $CXX eq '' ;

my $emptyfile = '.empty.cpp' ;
system( "touch $emptyfile" ) ;

my $cmd = "$CXX '-###' -c $emptyfile -std=c++11" ;
my $out = `$cmd 2>&1` ;
chomp $out ;
#print "$out\n" ;

# g++ -v empty.cpp shows the following order
#ignoring nonexistent directory "/home/peeterj/clang/optimized/lib/gcc/x86_64-unknown-linux-gnu/4.7.2/../../../../x86_64-unknown-linux-gnu/include"
##include "..." search starts here:
##include <...> search starts here:
# /home/peeterj/clang/optimized/lib/gcc/x86_64-unknown-linux-gnu/4.7.2/../../../../include/c++/4.7.2
# /home/peeterj/clang/optimized/lib/gcc/x86_64-unknown-linux-gnu/4.7.2/../../../../include/c++/4.7.2/x86_64-unknown-linux-gnu
# /home/peeterj/clang/optimized/lib/gcc/x86_64-unknown-linux-gnu/4.7.2/../../../../include/c++/4.7.2/backward
# /home/peeterj/clang/optimized/lib/gcc/x86_64-unknown-linux-gnu/4.7.2/include
# /usr/local/include
# /home/peeterj/clang/optimized/include
# /home/peeterj/clang/optimized/lib/gcc/x86_64-unknown-linux-gnu/4.7.2/include-fixed
# /usr/include
#
# The path:
#   /home/peeterj/clang/optimized/lib/gcc/x86_64-unknown-linux-gnu/4.7.2/include
# probably needs to be replaced for clang by:
#   "/home/peeterj/clang/optimized/bin/../lib/clang/3.3/include"
#
# clang -v shows:
#ignoring nonexistent directory "/include"
##include "..." search starts here:
##include <...> search starts here:
# /home/peeterj/clang/optimized/lib/gcc/x86_64-unknown-linux-gnu/4.7.2/../../../../include/c++/4.7.2
# /home/peeterj/clang/optimized/lib/gcc/x86_64-unknown-linux-gnu/4.7.2/../../../../include/c++/4.7.2/x86_64-unknown-linux-gnu
# /home/peeterj/clang/optimized/lib/gcc/x86_64-unknown-linux-gnu/4.7.2/../../../../include/c++/4.7.2/backward
# /usr/local/include
# /home/peeterj/clang/optimized/bin/../lib/clang/3.3/include
# /usr/include
#End of search list.
# ... think my issue is one of the defines not being right.  I've got all the actual includes.

my $output = qq%
// HeaderSearchOptions.h appears buggy.  It can not be included it without first including other stuff, and then only if the namespace is llvm?
//#include "llvm/ADT/StringRef.h"
//using namespace llvm ;
//#include "clang/Lex/HeaderSearchOptions.h"
//void AddSystemPaths( clang::HeaderSearchOptions * const headerSearchOptions )
{
% ;

#my $first = 1 ;
while ( $out =~ s/"([^"]+-isystem)" "([^"]+)"// )
{
   my ($isystem, $path) = ($1, $2) ;
   my $externc = 'false' ;

   if ( $isystem =~ /externc/ )
   {
      $externc = 'true' ;
   }

#   if ( $first )
#   {
#      $output .= genAddPath( $externc, qq("$path/tr1") ) ;
#
#      $first = 0 ;
#   }

   $output .= genAddPath( $externc, qq("$path") ) ;

#   print "$1 : $2\n" ;
}

$output .= "
}
" ;

print $output ;

exit ;

#  void AddPath(StringRef Path, frontend::IncludeDirGroup Group,
#               bool IsFramework, bool IgnoreSysRoot) {
sub genAddPath
{
   my ( $externc, $path ) = @_ ;

# externC param of AddPath now removed.
   return "
   headerSearchOptions->AddPath( $path,
                                 clang::frontend::Angled,
                                 false, // IsFramework
                                 false  // IgnoreSysRoot
                               ) ;
" ;
}
