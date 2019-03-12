#include <stdio.h>
#include "ut_threads.h"

void busywait(unsigned int n)
{
  for (; n > 0; n--)
        if (n % 100 == 0)
            ut_yield(); 
}

// function without calling ut_finish or ut_yield
int func_a(int id){
  int i = 0;
  for( ; i <50; i++){
    printf(" -=A%d=- ", ut_getid());
    busywait(0x1FFFFF);
  }
  return id;
}

// function that calls ut_finish but not ut_yield
void func_b(int id){
  int i = 0;
  for( ; i <50; i++){
    printf(" -=B%d=- ", ut_getid());
    busywait(0x1FFFFF);
  }
  ut_finish(id);
}

// function that calls both ut_finish and ut_yield
void func_c(int id){
  int i = 0;
  for( ; i <10; i++){
    printf(" -=C%d=- ", ut_getid());
    ut_yield();
  }
  ut_finish(id);
    printf(" Should not get here! \n");
}

// function that calls ut_yield but not ut_finish
int func_d(int id){
  int i = 0;
  for( ; i <100; i++){
    printf(" -=D%d=- ", ut_getid());
    ut_yield();
  }
  return id;
}

// function that does random math, returns sum
void func_e(int id){
  int i = 0;
  int sum = 0;
  for( ; i <10; i++){
    printf(" -=E%d=- ", ut_getid());
    sum += i;
    ut_yield();
  }
  ut_finish(sum);
    printf(" Should not get here! \n");
}

// function that uses recursion and does not call ut_finish or ut_yield with unique priority
int func_f(int id){
  if(id > 0)
  {
    printf(" -=F%d=- ", ut_getid());
    busywait(0x1FFFFF);
    func_f(--id);
  }
  else
  {
    return id;
  }
}

// function that uses recursion and does not call ut_finish or ut_yield with shared priority
int func_g(int id){
   if(id > 0)
  {
    printf(" -=G%d=- ", ut_getid());
    busywait(0x1FFFFF);
    func_g(--id);
  }
  else
  {
    return id;
  }
}

// function that sums up the id passed to it
int func_h(int id){
  int i = 0;
  int sum = 0;
    for( ; i <10; i++){
      printf(" -=H%d=- ", ut_getid());
      busywait(0x1FFFFF);
      sum += id;
      ut_yield();
    }
    return sum;
}

// same as func_c
int func_i(int id){
  return func_h(id);
}

int main()
{
  char threadstackbuf[MAX_THREADS * STACK_SIZE];
    
  printf("User-level Threads Scheduler\n");
  setvbuf(stdout, 0, _IONBF, BUFSIZ);

  ut_init(threadstackbuf);
  
  printf("Hello! I'm the main thread, my ID is %d.\n", ut_getid());
  printf("Now I'll create another 3 threads and wait until their jobs finish!\n");
  
  // create threads that use priorities to show priority
  int thrA = ut_create(&func_a, 1979,10);
  int thrB = ut_create(&func_b, 2008,9);
  int thrC = ut_create(&func_c, 29,8);
  int thrD = ut_create(&func_d, 1999,7);
  int thrE = ut_create(&func_e, 20,6);
  int thrF = ut_create(&func_f, 300,5);

  // create threads with same priority to show round robbin
  int thrG = ut_create(&func_g, 300,4);
  int thrH = ut_create(&func_h, 2030,4);
  int thrI = ut_create(&func_i, 290,4);
  int thrJ = ut_create(&func_i, 197,1);  // should not initialize because threads will be maxed out

  printf("THREAD A SUCCESS? (POSSITIVE IF SUCCESS) %d\n", thrA);
  printf("THREAD B SUCCESS? (POSSITIVE IF SUCCESS) %d\n", thrB);
  printf("THREAD C SUCCESS? (POSSITIVE IF SUCCESS) %d\n", thrC);
  printf("THREAD D SUCCESS? (POSSITIVE IF SUCCESS) %d\n", thrD);
  printf("THREAD E SUCCESS? (POSSITIVE IF SUCCESS) %d\n", thrE);
  printf("THREAD F SUCCESS? (POSSITIVE IF SUCCESS) %d\n", thrF);
  printf("THREAD G SUCCESS? (POSSITIVE IF SUCCESS) %d\n", thrG);
  printf("THREAD H SUCCESS? (POSSITIVE IF SUCCESS) %d\n", thrH);
  printf("THREAD I SUCCESS? (POSSITIVE IF SUCCESS) %d\n", thrI);
  printf("THREAD J SUCCESS? (POSSITIVE IF SUCCESS) %d\n", thrJ);  // should be negative
 
  int retA, retB, retC, retD, retE, retF, retG, retH, retI, retJ;
  
  ut_join(thrB, &retB);
  ut_join(thrA, &retA);
  ut_join(thrC, &retC);
  ut_join(thrE, &retE);
  ut_join(thrD, &retD);
  ut_join(thrF, &retF);
  ut_join(thrI, &retI);
  ut_join(thrG, &retG);
  ut_join(thrH, &retH);
  ut_join(thrJ, &retJ);
  
  printf("\n\n");
  printf("Thread A returned %d\n", retA); // should be 1979
  printf("Thread B returned %d\n", retB); // should be 2008
  printf("Thread C returned %d\n", retC); // should be 29
  printf("Thread D returned %d\n", retD); // should be 1999
  printf("Thread E returned %d\n", retE); // should be 45
  printf("Thread F returned %d\n", retF); // should be 0
  printf("Thread G returned %d\n", retG); // should be 0
  printf("Thread H returned %d\n", retH); // should be 20300
  printf("Thread I returned %d\n", retI); // should be 2900
  printf("Thread J returned %d\n", retJ); // should be 0

  
  printf("I`m also done ! Bye ...\n");

  return 0;
}
