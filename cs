exec.c:  cprintf("eip: 0x%x\n", curproc->tf->eip); 
exec.c:  curproc->tf->eip = curproc->codes;  // main
exec.c:  curproc->tf->esp = sp;
proc.c:  p->tf->cs = (SEG_UCODE << 3) | DPL_USER;
proc.c:  p->tf->ds = (SEG_UDATA << 3) | DPL_USER;
proc.c:  p->tf->es = p->tf->ds;
proc.c:  p->tf->ss = p->tf->ds;
proc.c:  p->tf->eflags = FL_IF;
proc.c:  p->tf->esp = PGSIZE;
proc.c:  p->tf->eip = 0;  // beginning of initcode.S
proc.c:  cprintf("\neip in fork: 0x%x\n\n", curproc->tf->eip - 0x381);
proc.c:  np->tf->eax = 0;
proc.c:  np->tf->eax = 0;
syscall.c:  return fetchint((myproc()->tf->esp) + 4 + 4*n, ip);
syscall.c:  num = curproc->tf->eax;
syscall.c:    curproc->tf->eax = syscalls[num]();
syscall.c:    curproc->tf->eax = -1;
trap.c:  if(tf->trapno == T_SYSCALL){
trap.c:  switch(tf->trapno){
trap.c:            cpuid(), tf->cs, tf->eip);
trap.c:    if(myproc() == 0 || (tf->cs&3) == 0){
trap.c:              tf->trapno, cpuid(), tf->eip, rcr2());
trap.c:            myproc()->pid, myproc()->name, tf->trapno,
trap.c:            tf->err, cpuid(), tf->eip, rcr2());
trap.c:  if(myproc() && myproc()->killed && (tf->cs&3) == DPL_USER)
trap.c:     tf->trapno == T_IRQ0+IRQ_TIMER)
trap.c:  if(myproc() && myproc()->killed && (tf->cs&3) == DPL_USER)
vm.c:       cprintf("eip: %d\n", curproc->tf->eip);
