#!/bin/bash
 
#ltrace -A 100 /usr/sbin/sendmail -t 2>&1 <<EOF
#strace /usr/sbin/sendmail -t 2>&1 <<EOF
#To: peeterjoot@pm.me
#To: peeter.joot@lzlabs.com
/usr/sbin/sendmail -t 2>&1 <<EOF
To: peeter.joot@lzlabs.com
From: peeter.joot@lzlabs.com
Subject: email test: `hostname`, `date`
test email body.
EOF
echo "RC: $?"
