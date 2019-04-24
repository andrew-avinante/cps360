# Program 6: XV6 Filesystem

## Time Spent - 20 Hours

## Implemented Features

* cp command
* RAM disk
* 64k support for RAM disk
    * The way I managed the allocation of memory was by defining a datablock struct which contained a pointer to the data and a flag to tell if a block is allocated or not. Whenever the RAM disk is being written to, the write function checks whether the offset is in the current datablock range or should be in the next (using intiger division). If it belongs in the next block and the next block is not allocated, then the writing function allocates the data and the allocated flag gets set to 1.  
    ![Diagram](diagram.png "Diagram")

## Bug Report

* p [echo to /tmp/e]: ** Doesn't work **
* cp [grep to /wc]: ** Doesn't work ** 
* OFFICIAL TEST CASE -> For the last two cp tests, I output the expected output but it says it got '' even though the output is right above the error message

```
aavin894@ubuntu:~/Desktop/cps360/Programs/Prog6$ sudo make qemu
No rule to make target fs/README.md
./tools/mkfs fs.img fs
used 29 (bit 1 ninode 26) free 29 total 1024
stressfs
sh
grep
mkdir
wc
ln
zombie
echo
halt
forktest
init
tester
cat
rm
kill
ls
balloc: first 443 blocks have been allocated
balloc: write bitmap block at sector 28
Ctrl+a h for help
qemu-system-i386 -serial mon:stdio -drive file=xv6.img,index=0,media=disk,format=raw -drive file=fs.img,index=1,media=disk,format=raw -drive file=test.img,index=2,media=disk,format=raw -smp 2 -device isa-debug-exit,iobase=0xf4,iosize=0x04  
xv6...
Have disk 2!
lapicinit: 1 0xfee00000
cpu1: starting
cpu0: starting
init: starting sh
$ echo bob > bob.txt
$ cat bob.txt
bob
$ cp bob.txt bob2.txt
$ cat bob2.txt
bob
$ cp test /ram/t.txt
Source file does not exist.
$ echo sdf > bob2.txt
$ cat bob2.txt
sdf
$ cp bob.txt bob2.txt
$ cat bob2.txt
bob
$ cp bob.txt j.txt
$ cat j.txt
bob
$ mkdir test
$ cp test bob.txt
Source may not be a directory.
$ cp bob.txt test
Destination may not be a directory.
$ echo abc > /ram/abc.txt
$ cat /ram/abc.txt
abc
$ echo 1 > /ram/1.txt
$ echo 2 > /ram/2.txt
$ echo 3 > /ram/3.txt
$ echo 4 > /ram/4.txt
$ cat /ram/1.txt
1
$ cat /ram/2.txt
2
$ cat /ram/3.txt
3
$ cat /ram/4.txt
4
$ cp /ram/1.txt /ram/5.txt
cat /ram/5.txt
1
$ echo hello > /ram/hello.txt
$ echo README > README
$ cp README > /ram/README
$ echo /ram/README
/ram/README
$ cat /ram/README
$ echo README > /ram/README
$ cat /ram/README
README
$ echo /ram/hello.txt
/ram/hello.txt
$ halt
Makefile:145: recipe for target 'qemu' failed
make: *** [qemu] Error 1
aavin894@ubuntu:~/Desktop/cps360/Programs/Prog6$ 
```