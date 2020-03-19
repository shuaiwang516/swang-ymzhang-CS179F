#include "types.h"
#include "user.h"

#define num 10000

#pragma GCC push_options
#pragma GCC optimize ("O0")
// recursive function to test the growing of the stack
static int
recurse(int n)
{
  if(n == 0)
    return 0;
  return n + recurse(n - 1);
}
#pragma GCC pop_options

int
main(int argc, char *argv[])
{
//======================================================function test======================================================//
  printf(1,"================================================function test================================================\n");
  int n, m;
  printf(1, "----------ASLR----------\n");
  printf(1, "stack position: 0x%x\n", getstackpos());
  printf(1, "heap position: 0x%x\n", getheappos());  
  printf(1, "----------ASLR----------\n");

  if(argc != 2){
    printf(1, "Usage: %s levels\n", argv[0]);
    exit();
  }

  n = atoi(argv[1]);
  //printf(1, "The sum from 1 to %d is %d\n", n);
  m = recurse(n);
  printf(1, "The sum from 1 to %d is %d\n", n, m);
  //printf(1, "%d\n", m);
  printf(1, "This process uses %d stack pages\n", getstackpg());
  printf(1, "The stack top position 0x%x\n", getstackpos() - getstackpg()*4096);   
  printf(1,"function test success!!!\n");

  printf(1,"\n================================================Performance test================================================\n");

  int timeInit = uptime();
  int retPid = fork();
  if(retPid == 0){
    exec("aslr",argv);
    exit();
  }

  if(retPid > 0)
  {
    wait();
    int time = uptime();
    time = time - timeInit;
    int decim = time % 1000;
    time /= 1000;
    if(decim < 10)
      printf(1, "ASLR ran in %d.00%d seconds\n", time, decim);
    else if(decim < 100 && decim >= 10)
      printf(1, "ASLR ran in %d.0%d seconds\n", time, decim);
    else
      printf(1, "ASLR ran in %d.%d seconds\n", time, decim);
  }


  printf(1,"\n================================================Stress test================================================\n");
  printf(1,"\nFork multiple process to make sure all the processes work under the ASLR!\n");
  int i;
  int pid;
  for(i = 0; i < num; i++){
    if((pid = fork()) == 0){
      sleep(100);
      exit();
    }
  }
  for(i = 0; i < num; i++){
    wait();
  }
  printf(1,"Stress test success!!!\n");


  exit();
}
