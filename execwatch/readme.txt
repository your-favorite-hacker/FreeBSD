execWatch
=========
module for logging every execution of tools on freebsd. logs will go directly to /var/log/messages.

usage
=====

root@crashb0x:~/execWatch # make
Warning: Object directory not changed from original /root/execWatch
cc -O2 -pipe  -fno-strict-aliasing -Werror -D_KERNEL -DKLD_MODULE -nostdinc   -I. -I@ -I@/contrib/altq -fno-common  -fno-omit-frame-pointer -mno-omit-leaf-frame-pointer  -mno-aes -mno-avx -mcmodel=kernel -mno-red-zone -mno-mmx -mno-sse -msoft-float  -fno-asynchronous-unwind-tables -ffreestanding -fstack-protector -std=iso9899:1999 -Qunused-arguments  -fstack-protector -Wall -Wredundant-decls -Wnested-externs -Wstrict-prototypes  -Wmissing-prototypes -Wpointer-arith -Winline -Wcast-qual  -Wundef -Wno-pointer-sign -fformat-extensions  -Wmissing-include-dirs -fdiagnostics-show-option  -Wno-error-tautological-compare -Wno-error-empty-body  -Wno-error-parentheses-equality -Wno-error-unused-function   -c execWatch.c
ld  -d -warn-common -r -d -o execWatch.ko execWatch.o
:> export_syms
awk -f /sys/conf/kmod_syms.awk execWatch.ko  export_syms | xargs -J% objcopy % execWatch.ko
objcopy --strip-debug execWatch.ko

root@crashb0x:~/execWatch # kldload ./execWatch.ko
[+] Loaded execWatch 0.1
[+] Call at 210

root@crashb0x:~/execWatch # kldstat
Id Refs Address            Size     Name
 1    3 0xffffffff80200000 1755658  kernel
 2    1 0xffffffff81a11000 326      execWatch.ko

root@crashb0x:~/execWatch # /usr/bin/id
uid=0(root) gid=0(wheel) groups=0(wheel),5(operator)

root@crashb0x:~/execWatch # tail -20 /var/log/messages
[...]
May 31 12:09:41 crashb0x kernel: execWatch: fname: /sbin/kldload (kldload) 2 uid: 0
May 31 12:09:47 crashb0x kernel: execWatch: fname: /sbin/kldunload (kldunload) 2 uid: 0
May 31 12:10:00 crashb0x kernel: execWatch: fname: /bin/sh (/bin/sh) 3 uid: 0
May 31 12:10:00 crashb0x kernel: execWatch: fname: /usr/libexec/atrun (/usr/libexec/atrun) 1 uid: 0
May 31 12:10:52 crashb0x kernel: execWatch: fname: /usr/bin/id (/usr/bin/id) 1 uid: 0
May 31 12:10:59 crashb0x kernel: execWatch: fname: /sbin/kldstat (kldstat) 1 uid: 0
May 31 12:11:00 crashb0x kernel: execWatch: fname: /bin/sh (/bin/sh) 3 uid: 2
May 31 12:11:00 crashb0x kernel: execWatch: fname: /usr/libexec/save-entropy (/usr/libexec/save-entropy) 1 uid: 2
May 31 12:11:00 crashb0x kernel: execWatch: fname: /sbin/sysctl (/sbin/sysctl) 3 uid: 2
May 31 12:11:00 crashb0x kernel: execWatch: fname: /bin/dd (dd) 5 uid: 2

ps
==
btw. it has its own syscall, which is obsolete, just ignore it. check the code if in doubt ;)

author
======
dash
