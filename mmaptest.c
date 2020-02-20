#include "types.h"
#include "user.h"

int main(int argc, char **argv){
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
  printf(1,"==========================================================\n");
  printf(1,"\n%s\n",text2);
  printf(1,"\n=========================================================\n");
  printf(1,"After we mmap the file, we have %d pages\n",getNumberOfUnusedPage());


  exit();
}
