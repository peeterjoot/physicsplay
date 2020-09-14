#!/usr/bin/perl
use MIME::Lite;

# dependency hell.  Tried:
#wget https://rpmfind.net/linux/epel/7/x86_64/Packages/p/perl-MIME-Lite-3.030-1.el7.noarch.rpm
#wget https://rpmfind.net/linux/epel/7/x86_64/Packages/p/perl-MIME-Types-1.38-2.el7.noarch.rpm
#wget https://rpmfind.net/linux/fedora-secondary/development/rawhide/Everything/s390x/os/Packages/p/perl-Email-Date-1.104-19.fc33.noarch.rpm
#
#sudo rpm -ivh perl-MIME-Lite-3.030-1.el7.noarch.rpm
#sudo rpm -ivh perl-Email-Date-1.104-19.fc33.noarch.rpm
#sudo rpm -ivh perl-MIME-Types-1.38-2.el7.noarch.rpm
#
# but get:
#
# error: Failed dependencies:
#   perl(:MODULE_COMPAT_5.32.0) is needed by perl-Email-Date-1.104-19.fc33.noarch
#   perl(Email::Abstract) is needed by perl-Email-Date-1.104-19.fc33.noarch
#   perl(Email::Date::Format) >= 1.000 is needed by perl-Email-Date-1.104-19.fc33.noarch
#   perl(Time::Piece) >= 1.08 is needed by perl-Email-Date-1.104-19.fc33.noarch
#   rpmlib(PayloadIsZstd) <= 5.4.18-1 is needed by perl-Email-Date-1.104-19.fc33.noarch

$to = 'peeter.joot@lzlabs.com';
#$cc = 'efgh@mail.com';
$from = 'peeter.joot@lzlabs.com';
$subject = 'Test Email';
$message = 'This is test email sent by Perl Script: mailme2.pl';

$msg = MIME::Lite->new(
                 From     => $from,
                 To       => $to,
                 #                 Cc       => $cc,
                 Subject  => $subject,
                 Data     => $message
                 );
                 
$msg->send;
print "Email Sent Successfully\n";
