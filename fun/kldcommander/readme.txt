kldcommander
============

fun module changing output values of kldstat firsts entry 'kernel'.

# uname -a
FreeBSD fbsd_default 9.3-RELEASE FreeBSD 9.3-RELEASE #0 r268512: Fri Jul 11 03:13:02 UTC 2014     root@snap.freebsd.org:/usr/obj/usr/src/sys/GENERIC  i386

Before loading:

root@fbsd:~ # kldstat 
Id Refs Address    Size     Name
 1    1 0xc0400000 1289f7c  kernel

After loading:

root@fbsd:~ # kldstat
Id Refs Address    Size     Name
 1    3 0xc0400000 1337     commander
 2    1 0xc48f0000 2000     kldhook.ko

root@fbsd:~ # kldstat -v
Id Refs Address    Size     Name
 1    3 0xc0400000 1337     commander (/boot/kernel/kernel)

Author
======
dash
