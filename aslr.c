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
  n = atoi(argv[1]);
  m = recurse(n);
  printf(1,"in aslr!! m = %d\n",m);
  exit();
}
