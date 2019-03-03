sudo mknod /dev/encrypt c 62 0
sudo chmod 666 /dev/encrypt

make
sudo insmod encrypt.ko
make rot47