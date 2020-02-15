#include "types.h"
#include "user.h"

int main(int argc, char **argv){
  int fd = open("README",0);
  char* text = mmap(fd);
  //int i;
  printf(1,"before we open the file, we have %d pages\n",getNumberOfUnusedPage());
  text[80] = 0;
 // printf(1,"%c\n", text[0]);
 // printf(1,"%c\n", *(text + 10));


  printf(1,"==========================================================\n");
 // printf(1,"The first address is :%d\n",text);
 // printf(1,"The first address is :%d\n",text[0]);
 // printf(1,"The text[80] address is : %p\n",text+80);
 // printf(1,"The text[80] address is : %p\n",text[80]);
 //for(i = 0; i < 5000; i++)
 //   printf(1,"%c",text[i]);
  printf(1,"%s\n",text);
  printf(1,"\n=========================================================\n");
  printf(1,"After we mmap the file, we have %d pages\n",getNumberOfUnusedPage());
  
  int fd2 = open("README",0);
  char *text2 = mmap(fd2);
  text2[80] = 0;
  printf(1,"before we open the file, we have %d pages\n",getNumberOfUnusedPage());
  printf(1,"==========================================================\n");
  printf(1,"%s\n",text2);
  printf(1,"\n=========================================================\n");
  printf(1,"After we mmap the file, we have %d pages\n",getNumberOfUnusedPage());


  exit();
}



/*#include"types.h"
#include"user.h"
int main(int argc, char** argv) {
  printf(1,"About to make first mmap. Next, you should see the first sentence from README\n");
  int fd = open("README",0);  
  char* text = mmap(fd);
  printf(1,"before we open the file, we have %d pages\n",getNumberOfUnusedPage());
  text[85]=0;
  if(text!=(void*)0x40000000)
    printf(1,"Returned pointer is %d, should be 1073741824 (0x40000000)\n",text);
  printf(1,"%s\n",text);
  printf(1,"After we mmap the file, we have %d pages\n",getNumberOfUnusedPage());

  printf(1,"\nSecond mmap coming\n");
  int fd2 = open("LICENSE",0);  
  char* text2 = mmap(fd2);
  printf(1,"text2 start addr = %d\n",text2);  
  //text2[50]=0;
  if(text2!=(void*)0x40001000)
    printf(1,"Returned pointer is %d, should be 1073741824+4069 (0x40001000)\n",text2);
  printf(1,"%s\n",text2);

  printf(1,"Checking that first mmap is still ok, you should see the first sentence from README\n");
  text[85]=0;
  if(text!=(void*)0x40000000)
    printf(1,"Returned pointer is %d, should be 1073741824 (0x40000000)\n",text);
  printf(1,"%s\n",text);

  exit();
}*/
