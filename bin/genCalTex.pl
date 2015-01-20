#!/usr/bin/perl

my @chars = ("A".."Z") ;
push( @chars, ("a".."z") ) ;

foreach my $c (@chars)
{
   print "\\newcommand{\\cal$c}[0]{{\\mathcal{$c}}}\n" ;
}

foreach my $c (@chars)
{
   print "\\newcommand{\\bc$c}[0]{{\\bm{\\mathcal{$c}}}}\n" ;
}
