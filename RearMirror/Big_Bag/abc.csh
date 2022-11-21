#!/bin/csh -f

alias clean 'rm -f abc rb rb.orig'

clean

gcc -Wall -Wextra -O3 -o abc abc.c

openssl rand -base64 1000000 > rb

cp --archive rb rb.orig

./abc rb

diff rb.orig rb

clean

