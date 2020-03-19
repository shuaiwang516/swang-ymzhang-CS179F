#include "types.h"
#include "user.h"

int main(int argc, char **argv){
  int fd = open("CS179F1",0);
  char* text = mmap(fd);
  text[80] = 0;
  close(fd);
  exit();
}
