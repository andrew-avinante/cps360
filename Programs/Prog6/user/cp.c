#include "types.h"
#include "stat.h"
#include "user.h"
#include "fcntl.h"

void
cp(int fds, int fdd, struct stat fileStat, char* str)
{

    char buf[1024];
    int writes = 0;
    while ((writes = read(fds, buf, sizeof(buf)))!= 0)
    {
        write(fdd, buf, writes);
        memset(&buf, 0, sizeof(buf));
    }
}

int
main(int argc, char *argv[])
{
    if(argc < 2){
        printf(1, "Usage: cp <source> <destination>\n");
        exit();
    }

    struct stat fileStat;

    stat(argv[1], &fileStat);
    if(fileStat.type == 1)
    {
        printf(1, "Source may not be a directory.\n");
        exit();
    }
    else if(fileStat.type == 0)
    {
        printf(1, "Source file does not exist.\n");
        exit();
    }

    stat(argv[2], &fileStat);
    if(fileStat.type == 1 || fileStat.type == 0)
    {
        printf(1, "Destination may not be a directory.\n");
        exit();
    }

    int fds = open(argv[1], O_RDONLY);
    int fdd = open(argv[2], O_WRONLY | O_CREATE);


    cp(fds, fdd, fileStat, argv[1]);

    exit();
}
