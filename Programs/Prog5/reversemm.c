#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <unistd.h>


int main(int argc, char *argv[])
{
    char *buf;
    int size;
    struct stat s;
    int fd = open(argv[1], O_RDWR);
    int stat = fstat(fd, &s);
    size = s.st_size;
    buf = mmap(NULL, size, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    char temp[10];
    for(size_t i = 0, j = size-1; i < size/2; i++, j--) {
        char h = buf[j];
        buf[j] = buf[i];
        buf[i] = h;
    }
    msync(buf, size, MS_SYNC);
    munmap(buf, size);
    close(fd);
}