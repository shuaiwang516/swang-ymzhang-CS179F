#include "types.h"
#include "user.h"


int data = 5;

int main(int argc, char *argv[])
{
  int pid;
  
//==============================================function test====================================================//
  printf(1,"===========================function test=============================\n");
  pid = forkCoW();

  if(pid == 0){
    printf(1,"This is CoW fork!\n");
    printf(1,"C1:Before change data, data = %d, we have %d Unused Pages\n", data, getNumberOfUnusedPage());
    data = 10;
    printf(1,"C1:After change data, data = %d,  we have %d Unused Pages\n",data , getNumberOfUnusedPage()); 
    exit();
  }
  

  int pid2;
  pid2 = fork();
  
  if(pid2 == 0){
    printf(1,"This is normal fork!\n");
    printf(1,"C1:Before change data, data = %d, we have %d Unused Pages\n", data, getNumberOfUnusedPage());
    data = 20;
    printf(1,"C1:After change data, data = %d,  we have %d Unused Pages\n",data , getNumberOfUnusedPage()); 
    exit();
  }
  wait();
  wait();
  printf(1,"\nfunction test success!!!\n\n");


//=============================================Performance test========================================================//
  printf(1,"==========================Performance test============================\n");

  int timeInit = uptime();
  int retPid = fork();
  if(retPid == 0){
    exec("cow",argv);
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
      printf(1, "copy-on-write ran in %d.00%d seconds\n", time, decim);
    else if(decim < 100 && decim >= 10)
      printf(1, "copy-on-write ran in %d.0%d seconds\n", time, decim);
    else
      printf(1, "copy-on-write ran in %d.%d seconds\n", time, decim);
  }


//===============================================Stress test==========================================================//
  printf(1,"\n============================Stress test==============================\n");
  printf(1,"Totally fork 10000 child processes!\n");
  int pidarray[10000];
  int i;
  int testdata = 0;
  printf(1,"Parent testdata = %d, Change testdata in Child to 1\n", testdata);

  for(i = 0; i < 10000; i++){
    if((pidarray[i] = forkCoW()) == 0){
      testdata = 1;
      sleep(100);
      exit();    
    }
  }
  int j;
  for(j = 0; j < 10000; j++)
    wait();

  printf(1,"\nStress test success!!!\n\n");



  exit();
}
