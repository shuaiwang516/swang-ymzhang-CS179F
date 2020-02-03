#include "types.h"
#include "user.h"

int data = 5;
int main(int argc, char *argv[])
{
  int pid;
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
  exit();
}
