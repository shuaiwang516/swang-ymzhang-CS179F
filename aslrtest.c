#include "types.h"
#include "user.h"

#pragma GCC push_options
#pragma GCC optimize ("O0")
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
  exit();
}
