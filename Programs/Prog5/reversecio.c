#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <unistd.h>


int main(int argc, char *argv[])
{
    int size;
    struct stat s;
    FILE *fd = fopen(argv[1], "r+");
    int stat = fstat(fileno(fd), &s);
    size = s.st_size;
    char *buf = malloc(size);
    fread(buf, 1, size, fd);
    for(size_t i = 0, j = size-1; i < size/2; i++, j--)
    {
        char h = buf[j];
        buf[j] = buf[i];
        buf[i] = h;
    }
    fseek(fd, 0, SEEK_SET);
    fwrite(buf, 1, size, fd);
    fclose(fd);
}