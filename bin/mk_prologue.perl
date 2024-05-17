sub prologue
{
   my ( $name, $platforms, $replyto, $author ) = @_ ;

return qq%#!/usr/bin/perl

#-----------------------------------------------------------------------------
# POD Format Documentation.  Read "perldoc perlpod" for an example.
# When done, check syntax with "podchecker".

=head1 NAME

$name - <one-line-description>

=head1 SYNOPSIS

$name [--help] [<options>]

=head1 DESCRIPTION


Options:

=over 4

=item --foo=bar

Blah.

=back

=head1 SUPPORTED PLATFORMS
$platforms
=head1 SUPPORT

 Send email to $replyto

=head1 AUTHORS

 $author

=cut

#-----------------------------------------------------------------------------

use strict ;
use warnings ;
use Getopt::Long ;
use Pod::Usage ;

# Suppress sourcing of users' .bashrc files in invoked shells
delete \$ENV{'ENV'} ;
delete \$ENV{'BASH_ENV'} ;

# Set STDOUT and STDERR to unbuffered
select STDERR ; \$| = 1 ;
select STDOUT ; \$| = 1 ;

my \$myName = '' ;

(\$myName = \$0) =~ s\@.*[/\\\\]\@\@ ;

#Getopt::Long::Configure( 'pass_through' ) ;
GetOptions (
   'help'               => sub { pod2usage(-verbose => 2) ; },
) or pod2usage(-verbose => 0) ;

# Validate/handle options, and everything else...
% ;
}

1 ;
