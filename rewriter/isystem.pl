#!/usr/bin/perl

my $CXX = $ARGV[0] ;
die if $CXX eq '' ;

my $emptyfile = '.empty.cpp' ;
system( "touch $emptyfile" ) ;

my $cmd = "$CXX '-###' -c $emptyfile -std=c++11" ;
my $out = `$cmd 2>&1` ;
chomp $out ;
#print "$out\n" ;

my $output = qq%
// HeaderSearchOptions.h appears buggy.  It can not be included it without first including other stuff, and then only if the namespace is llvm?
//#include "llvm/ADT/StringRef.h"
//using namespace llvm ;
//#include "clang/Lex/HeaderSearchOptions.h"
//void AddSystemPaths( clang::HeaderSearchOptions * const headerSearchOptions )
{
% ;

my $first = 1 ;
while ( $out =~ s/"([^"]+-isystem)" "([^"]+)"// )
{
   my ($isystem, $path) = ($1, $2) ;
   my $externc = 'false' ;

   if ( $isystem =~ /externc/ )
   {
      $externc = 'true' ;
   }

   if ( $first )
   {
      $output .= genAddPath( $externc, qq("$path/tr1") ) ;

      $first = 0 ;
   }

   $output .= genAddPath( $externc, qq("$path") ) ;

#   print "$1 : $2\n" ;
}

$output .= "
}
" ;

print $output ;

exit ;

sub genAddPath
{
   my ( $externc, $path ) = @_ ;

   return "
   headerSearchOptions->AddPath( $path,
                                 clang::frontend::Angled,
                                 false, // IsUserSupplied
                                 false, // IsFramework
                                 false, // IgnoreSysRoot
                                 true, // IsInternal
                                 $externc ) ; // ImplicitExternC
" ;
}
