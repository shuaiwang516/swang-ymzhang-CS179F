#include "types.h"
#include "x86.h"
#include "defs.h"
#include "date.h"
#include "param.h"
#include "memlayout.h"
#include "mmu.h"
#include "proc.h"
//-----------cs179F-------------//
#include "spinlock.h"
#include "sleeplock.h"
#include "fs.h"
#include "file.h"
#include "fcntl.h"
//------------cs179F-------------//
int
sys_getNumberOfUnusedPage(void)
{
  return getNumberOfUnusedPage();
}

//---------------cs179F------------//
int
sys_forkCoW(void)
{
  return forkCoW();
}

int
sys_getstackpos(void)
{
  return myproc()->stackpos;
}

int
sys_getheappos(void)
{
  return myproc()->heappos;
}

int
sys_getstackpg(void)
{
  return myproc()->stackpg;
}

//--------------cs179F------------//
int
sys_mmap(void)
{
  int fd;
  struct file *f;
  argfd(0,&fd,&f); 
 /* struct proc *curproc = myproc();
  uint mPointer = curproc->mmapSz + MMAPBASE;
  char *startAddr = (char*) mPointer;
  uint endAddr;

  curproc->mfile[curproc->mfileIndex]->fileStartAddr = startAddr;
  endAddr = (uint) (curproc->mfile[curproc->mfileIndex]->fileStartAddr + f->ip->size);
  curproc->mfile[curproc->mfileIndex]->fileEndAddr = (char*) PGROUNDUP(endAddr);
  curproc->mfile[curproc->mfileIndex]->fd = fd;
  curproc->mfile[curproc->mfileIndex]->f = f;
  curproc->mmapSz = curproc->mmapSz + (uint) (curproc->mfile[curproc->mfileIndex]->fileEndAddr - curproc->mfile[curproc->mfileIndex]->fileStartAddr);
  curproc->mfileIndex++;
  return mPointer;*/
  return mmap(fd, f);
}

int
sys_fork(void)
{
  return fork();
}

int
sys_exit(void)
{
  exit();
  return 0;  // not reached
}

int
sys_wait(void)
{
  return wait();
}

int
sys_kill(void)
{
  int pid;

  if(argint(0, &pid) < 0)
    return -1;
  return kill(pid);
}

int
sys_getpid(void)
{
  return myproc()->pid;
}

int
sys_sbrk(void)
{
  int addr;
  int n;

  if(argint(0, &n) < 0)
    return -1;
  addr = myproc()->sz;
  if(growproc(n) < 0)
    return -1;
  return addr;
}

int
sys_sleep(void)
{
  int n;
  uint ticks0;

  if(argint(0, &n) < 0)
    return -1;
  acquire(&tickslock);
  ticks0 = ticks;
  while(ticks - ticks0 < n){
    if(myproc()->killed){
      release(&tickslock);
      return -1;
    }
    sleep(&ticks, &tickslock);
  }
  release(&tickslock);
  return 0;
}

// return how many clock tick interrupts have occurred
// since start.
int
sys_uptime(void)
{
  uint xticks;

  acquire(&tickslock);
  xticks = ticks;
  release(&tickslock);
  return xticks;
}
