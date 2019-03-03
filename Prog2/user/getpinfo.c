#include "types.h"
#include "pstat.h"
#include "user.h"


int
main(int argc, char *argv[])
{
    struct pstat *p = &(struct pstat){};
    getpinfo(p);
    printf(1, "PID  INUSE   TICKS   TICKETS\n");
    for(int i = 0; i < 64; i++)
    {
        if(p->pid[i] > 0)
        {
            printf(1, "%d    %d       %d       %d\n", p->pid[i], p->inuse[i], p->ticks[i], p->tickets[i]);
        }
    }
    exit();
}
