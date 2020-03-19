#include "types.h"
#include "user.h"

#define n 10
#define m 1000

int main(int argc, char **argv){

//===========================================function test======================================//
  printf(1,"================================================function test================================================\n");
  int fd = open("CS179F1",0);
  char* text = mmap(fd);
  //int i;
  printf(1,"before we open the file, we have %d pages\n",getNumberOfUnusedPage());
 // text[1000000] = 0;
 // printf(1,"%c\n", text[0]);
 // printf(1,"%c\n", *(text + 10));

  printf(1,"==========================================================\n");
 // printf(1,"The first address is :%d\n",text);
 // printf(1,"The first address is :%d\n",text[0]);
 // printf(1,"The text[80] address is : %p\n",text+80);
 // printf(1,"The text[80] address is : %p\n",text[80]);
 //for(i = 0; i < 5000; i++)
 //   printf(1,"%c",text[i]);
  printf(1,"\n%s\n",text);
  printf(1,"\n=========================================================\n");
  printf(1,"After we mmap the file, we have %d pages\n",getNumberOfUnusedPage());
  
  int fd2 = open("CS179F2",0);
  char *text2 = mmap(fd2);
  printf(1,"before we open the file, we have %d pages\n",getNumberOfUnusedPage());
  printf(1,"===========================================================\n");
  printf(1,"\n%s\n",text2);
  printf(1,"\n=========================================================\n");
  printf(1,"After we mmap the file, we have %d pages\n",getNumberOfUnusedPage());

  printf(1,"function test success!!!\n");
  close(fd);
  close(fd2);

  printf(1,"\n================================================Performance test================================================\n");

  int timeInit = uptime();
  int retPid = fork();
  if(retPid == 0){
    exec("mmap",argv);
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
      printf(1, "mmap ran in %d.00%d seconds\n", time, decim);
    else if(decim < 100 && decim >= 10)
      printf(1, "mmap ran in %d.0%d seconds\n", time, decim);
    else
      printf(1, "mmap ran in %d.%d seconds\n", time, decim);
  }




//===========================================Stress test======================================//
  printf(1,"\n=================================================Stress test=================================================\n");
  printf(1,"Test1: mmap %d files into memory.\n",n);

  int fdx[n];
  int i;
  for(i = 0; i < n; i++){
    fdx[i] = open("CS179F1",0);
    char* Stresstext = mmap(fdx[i]);
    Stresstext[80] = 0;
  }
  for(i = 0; i < n; i++){
    close(fdx[i]); 
  }
   
  printf(1,"%d files test success!!!\n\n",n);
  
  printf(1,"Test2: mmap %d files into memory.\n",m);
  int fdx2[m];
  int k;
  for(k = 0; k < m; k++){
    fdx[k] = open("CS179F1",0);
    char* Stresstext = mmap(fdx2[k]);
    Stresstext[80] = 0;
  }
  for(k = 0; k < n; k++){
    close(fdx2[k]);
  }

  printf(1,"%d files test success!!!\n",m);



  exit();
}
