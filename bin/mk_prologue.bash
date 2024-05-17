sub prologue
{
   my ( $name, $platforms, $replyto, $author ) = @_ ;

return qq%#!/bin/bash

: <<=cut
#-----------------------------------------------------------------------------
# POD like Format Documentation.  Invoke perldoc ./thisfile to see the documentation.
# See "perldoc perlpod" for examples.
# When done, check syntax with "podchecker".

=head1 NAME

$name - <one-line-description>

=head1 SYNOPSIS

$name [<options>]

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
% ;
}

1 ;
