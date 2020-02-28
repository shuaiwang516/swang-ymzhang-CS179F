#include "types.h"
#include "param.h"
#include "memlayout.h"
#include "mmu.h"
#include "proc.h"
#include "defs.h"
#include "x86.h"
#include "elf.h"

//---------------cs179F-----------//
#include "date.h"
#include "rand.h"

int
exec(char *path, char **argv)
{
  char *s, *last;
  int i, off;
  uint argc, sz, sp, ustack[3+MAXARG+1];
  struct elfhdr elf;
  struct inode *ip;
  struct proghdr ph;
  pde_t *pgdir, *oldpgdir;
  struct proc *curproc = myproc();
  //----------------cs179F----------------//
  int stackpos;
  struct rtcdate *r = 0;
  int base, codes; 

  begin_op();

  if((ip = namei(path)) == 0){
    end_op();
    cprintf("exec: fail\n");
    return -1;
  }
  ilock(ip);
  pgdir = 0;

  // Check ELF header
  if(readi(ip, (char*)&elf, 0, sizeof(elf)) != sizeof(elf))
    goto bad;
  if(elf.magic != ELF_MAGIC)
    goto bad;

  if((pgdir = setupkvm()) == 0)
    goto bad;

  // Load program into memory.
  //------------------cs179F--------------//
  //sz = 0;
  cmostime(r);
  srand(r->second);
  codes = rand()*0x8001;
  codes = PGROUNDDOWN(codes);
  curproc->codes = codes;
  for(i=0, off=elf.phoff; i<elf.phnum; i++, off+=sizeof(ph)){
    if(readi(ip, (char*)&ph, off, sizeof(ph)) != sizeof(ph))
      goto bad;
    if(ph.type != ELF_PROG_LOAD)
      continue;
    if(ph.memsz < ph.filesz)
      goto bad;
    if(ph.vaddr + ph.memsz < ph.vaddr)
      goto bad;
    //----------cs179F note-----------//
    //In this allocuvm, xv6 set page to PTE_W|PTE_U
    //if((sz = allocuvm(pgdir, sz, ph.vaddr + ph.memsz)) == 0)
    //  goto bad;
    if((base = allocuvm(pgdir, codes, codes + ph.vaddr + ph.memsz)) == 0)
      goto bad;
    if(ph.vaddr % PGSIZE != 0)
      goto bad;
    if(loaduvm(pgdir, (char*)(codes + ph.vaddr), ip, ph.off, ph.filesz) < 0)
      goto bad;
    codes = base;
  }
  iunlockput(ip);
  end_op();
  ip = 0;
  curproc->codee = codes;

  // Allocate two pages at the next page boundary.
  // Make the first inaccessible.  Use the second as the user stack.
  /*sz = PGROUNDUP(sz);
  if((sz = allocuvm(pgdir, sz, sz + 2*PGSIZE)) == 0)
    goto bad;
  clearpteu(pgdir, (char*)(sz - 2*PGSIZE));
  sp = sz;*/

  //--------------------CS179F--------------------//
  //cmostime(r);
  //srand(r->second);
  // RAND_MAX = 0x7fff, so we multiple 0x8001 to increase it to 0x3fffffff under MMAPBASE
  stackpos = rand()*0x8001;
  while(stackpos >= (curproc->codes - PGSIZE) && stackpos <= curproc->codee)
    stackpos = rand()*0x8001;
  stackpos = PGROUNDUP(stackpos);
  if((sp = allocuvm(pgdir, stackpos - PGSIZE, stackpos)) == 0)
    goto bad;
  //clearpteu(pgdir, (char*)stackpos - 2*PGSIZE);
  //cprintf("%x\n", sp);

  sz = rand()*0x8001;
  while((sz >= curproc->codes && sz <= curproc->codee + PGSIZE) || (sz >= stackpos - PGSIZE && sz <= stackpos + PGSIZE))
    sz = rand()*0x8001;
  sz = PGROUNDDOWN(sz);

  // Push argument strings, prepare rest of stack in ustack.
  for(argc = 0; argv[argc]; argc++) {
    if(argc >= MAXARG)
      goto bad;
    sp = (sp - (strlen(argv[argc]) + 1)) & ~3;
    if(copyout(pgdir, sp, argv[argc], strlen(argv[argc]) + 1) < 0)
      goto bad;
    ustack[3+argc] = sp;
  }
  ustack[3+argc] = 0;

  ustack[0] = 0xffffffff;  // fake return PC
  ustack[1] = argc;
  ustack[2] = sp - (argc+1)*4;  // argv pointer

  sp -= (3+argc+1) * 4;
  if(copyout(pgdir, sp, ustack, (3+argc+1)*4) < 0)
    goto bad;

  // Save program name for debugging.
  for(last=s=path; *s; s++)
    if(*s == '/')
      last = s+1;
  safestrcpy(curproc->name, last, sizeof(curproc->name));

  // Commit to the user image.
  oldpgdir = curproc->pgdir;
  curproc->pgdir = pgdir;
  curproc->sz = sz;
  curproc->tf->eip = curproc->codes;  // main
  curproc->tf->esp = sp;
  //---------------cs179F-----------//
  curproc->stackpos = stackpos;
  curproc->stackpg = 1;
  switchuvm(curproc);
  freevm(oldpgdir);
  //cprintf("\nmemlayout:\n");
  //cprintf("text+data: from 0x%x to 0x%x\n", curproc->codes,  curproc->codee);
  //cprintf("stack pointer: 0x%x\n", curproc->stackpos);
  //cprintf("heap pointer: 0x%x\n\n", curproc->sz);
  return 0;

 bad:
  if(pgdir)
    freevm(pgdir);
  if(ip){
    iunlockput(ip);
    end_op();
  }
  return -1;
}
