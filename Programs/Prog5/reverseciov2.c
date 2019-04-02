#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include <stdbool.h>


int main(int argc, char *argv[])
{
    int size;
    int stat;
    struct stat s;
    const int KB = 8;
    const int BLOCK_SIZE = 1024 * 8;
    
    FILE *fd = fopen(argv[1], "r+");
    stat = fstat(fileno(fd), &s);
    size = s.st_size;
    bool isSmaller = size < BLOCK_SIZE ? true : false;

    int startIndex = 0;
    int endIndex = size - BLOCK_SIZE;
    int nextStop;
    char *topBuf = malloc(BLOCK_SIZE);
    char *bottomBuf = malloc(BLOCK_SIZE);
    char h;
    int countUp = 0, countDown = size;

    for(; (endIndex - startIndex) * 2 > BLOCK_SIZE; countUp++, countDown--)
    {
        fseek(fd, startIndex, SEEK_SET);
        fread(topBuf, 1, BLOCK_SIZE, fd);
    
        fseek(fd, endIndex, SEEK_SET);
        fread(bottomBuf, 1, BLOCK_SIZE, fd);

        for(int i = 0, j = BLOCK_SIZE - 1; i < BLOCK_SIZE; i++, j--)
        {
            h = bottomBuf[j];
            bottomBuf[j] = topBuf[i];
            topBuf[i] = h;
        }
        fseek(fd, startIndex, SEEK_SET);
        fwrite(topBuf, 1, BLOCK_SIZE, fd);

        fseek(fd, endIndex, SEEK_SET);
        fwrite(bottomBuf, 1, BLOCK_SIZE, fd);
        startIndex += BLOCK_SIZE;
        endIndex -= BLOCK_SIZE;
    }
    int remain = endIndex - startIndex;

    if(remain > -1 || isSmaller)
    {
        remain += BLOCK_SIZE;
        char *buf = malloc(remain);
        fseek(fd, startIndex, SEEK_SET);
        fread(buf, 1, remain, fd);
        for(size_t i = 0, j = remain-1; i < remain/2; i++, j--)
        {
            char h = buf[j];
            buf[j] = buf[i];
            buf[i] = h;
        }
        fseek(fd, startIndex, SEEK_SET);
        fwrite(buf, 1, remain, fd);
        fclose(fd);
    }
    
    fclose(fd);
}