#include "types.h"
#include "user.h"

int main(int argc, char **argv){
  int fd = open("README",0);
  char* text = mmap(fd);
  int i;
  printf(1,"before we open the file, we have %d pages\n",getNumberOfUnusedPage());
  //text[80] = 0;

  printf(1,"==========================================================\n");
  for(i = 0; i < 80; i++)
    printf(1,"%c",text[i]);
  printf(1,"\n=========================================================\n");
  printf(1,"After we mmap the file, we have %d pages\n",getNumberOfUnusedPage());
  exit();
}
