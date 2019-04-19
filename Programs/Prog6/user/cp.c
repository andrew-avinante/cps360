#include "types.h"
#include "stat.h"
#include "user.h"
#include "fcntl.h"

void
cp(int fds, int fdd, struct stat fileStat, char* str)
{

    char buf[1024];
    if(fds != -1){
        while (read(fds, buf, fileStat.size))
        {
            write(fdd, buf, fileStat.size);
        }
    }
    else
    {
        write(fdd, str, strlen(str));
    }
}

int
main(int argc, char *argv[])
{
    if(argc < 2){
        printf(2, "Usage: cp <source> <destination>\n");
        exit();
    }

    struct stat fileStat;
    stat(argv[2], &fileStat);
    if(fileStat.type == 1)
    {
        printf(0, "Destination may not be a directory.\n");
        exit();
    }

    stat(argv[1], &fileStat);
    if(fileStat.type == 1)
    {
        printf(0, "Source may not be a directory.\n");
        exit();
    }

    int fds = open(argv[1], O_RDONLY);
    int fdd = open(argv[2], O_WRONLY | O_CREATE);


    cp(fds, fdd, fileStat, argv[1]);

    exit();
}
