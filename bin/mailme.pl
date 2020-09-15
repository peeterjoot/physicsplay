#!/usr/bin/perl
 
$to = 'peeter.joot@lzlabs.com';
$from = 'peeter.joot@lzlabs.com';
$subject = 'Test Email';
$message = 'This is test email sent by Perl Script (macos)';
 
open(MAIL, "|/usr/sbin/sendmail -t");
 
# Email Header
print MAIL "To: $to\n";
print MAIL "From: $from\n";
print MAIL "Subject: $subject\n\n";
# Email Body
print MAIL $message;

close(MAIL);
print "Email Sent Successfully\n";
