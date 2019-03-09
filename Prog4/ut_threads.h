
int ut_init();
int ut_create(void (* entry)(int), int, int);
void ut_yield();
int ut_getid();
void ut_finish(int);
int ut_join(int, int *);
void ut_return(int (* entry)(int), int);

#define MAX_THREADS 10
#define STACK_SIZE 1024