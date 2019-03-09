#include <stdio.h>
#include "ut_threads.h"

void busywait(unsigned int n)
{
    for (; n > 0; n--)
        if (n % 100 == 0)
            ut_yield(); 
}

int func_a(int id){
    int i = 0;
    printf(" -=A got %d ", id);
    for( ; i <50; i++){
        printf(" -=A%d=- ", ut_getid());
        ut_yield();
    }
    return id;
}

int func_b(int id){
    int i = 0;
    printf(" -=B got %d ", id);
    for( ; i <50; i++){
        printf(" -=B%d=- ", ut_getid());
        ut_yield();
    }
    return id;
}

void func_c(int id){
    int i = 0;
    for( ; i <10; i++){
        printf(" -=C%d=- ", ut_getid());
        ut_yield();
    }
    ut_finish(id);
    printf(" Should not get here! \n");
}

void func_d(int id){
    int i = 0;
    for( ; i <10; i++){
        printf(" -=D%d=- ", ut_getid());
        ut_yield();
    }
    ut_finish(id);
    printf(" Should not get here! \n");
}

int main()
{
    char threadstackbuf[MAX_THREADS * STACK_SIZE];
    
    printf("User-level Threads Scheduler\n");
    setvbuf(stdout, 0, _IONBF, BUFSIZ);

    ut_init(threadstackbuf);
    
    printf("Hello! I'm the main thread, my ID is %d.\n", ut_getid());
    printf("Now I'll create another 3 threads and wait until their jobs finish!\n");
    
    int thrA = ut_create(&func_a, 1979, 10);
    int thrB = ut_create(&func_b, 2008, 10);
    int thrC = ut_create(&func_c, 2012, 10);
    int thrD = ut_create(&func_d, 29, 5);
    
    int retA, retB, retC, retD;
    
    ut_join(thrB, &retB);
    ut_join(thrA, &retA);
    ut_join(thrC, &retC);
    ut_join(thrD, &retD);
    
    printf("\n\n");
    printf("Thread A returned %d\n", retA);
    printf("Thread B returned %d\n", retB);
    printf("Thread C returned %d\n", retC);
    printf("Thread D returned %d\n", retD);
    
    printf("I`m also done ! Bye ...\n");

    return 0;
}
