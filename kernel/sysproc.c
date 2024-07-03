#include "types.h"
#include "riscv.h"
#include "defs.h"
#include "param.h"
#include "memlayout.h"
#include "spinlock.h"
#include "proc.h"
#include "pstat.h"

uint64
sys_exit(void)
{
  int n;
  argint(0, &n);
  exit(n);
  return 0;  // not reached
}

uint64
sys_getpid(void)
{
  return myproc()->pid;
}

uint64
sys_fork(void)
{
  return fork();
}

uint64
sys_wait(void)
{
  uint64 p;
  argaddr(0, &p);
  return wait(p);
}

uint64
sys_sbrk(void)
{
  uint64 addr;
  int n;

  argint(0, &n);
  addr = myproc()->sz;
  if(growproc(n) < 0)
    return -1;
  return addr;
}

uint64
sys_sleep(void)
{
  int n;
  uint ticks0;

  argint(0, &n);
  acquire(&tickslock);
  ticks0 = ticks;
  while(ticks - ticks0 < n){
    if(killed(myproc())){
      release(&tickslock);
      return -1;
    }
    sleep(&ticks, &tickslock);
  }
  release(&tickslock);
  return 0;
}

uint64
sys_kill(void)
{
  int pid;

  argint(0, &pid);
  return kill(pid);
}

// return how many clock tick interrupts have occurred
// since start.
uint64
sys_uptime(void)
{
  uint xticks;

  acquire(&tickslock);
  xticks = ticks;
  release(&tickslock);
  return xticks;
}

uint64
sys_set_tickets(void)
{
  int tickets;
  struct proc *p = myproc();

  argint(0, &tickets);

  if(tickets < 1)
    return -1;

  //Define o número de tickets do processo atual
  p->tickets = tickets;
  return 0;
}

uint64
sys_getpinfo(void){
  struct pstat *p;
  if(argptr(0,(void*)&p, sizeof(*p)) < 0)
    return -1;

  struct proc *proc_atual = myproc();

  // Adquire o lock do process table (ptable)
  acquire(&ptable.lock);

  // Itera sobre todos os processos no ptable
  for(int i=0 ; i<NPROC ; i++){
    // Se o processo está em uso, preenche os campos correspondentes na struct pstat
    if(ptable.proc[i].state != UNUSED){
      p->inuse[i] = 1;
      p->tickets[i] = ptable.proc[i].tickets;
      p->pid[i] = ptable.proc[i].pid;
      p->ticks[i] = ptable.proc[i].ticks;
    }
    else{
      // Se o processo não está em uso, define o campo inuse como 0
      p->inuse[i] = 0;
    }

    // Libera o lock do process table
    release(&ptable.lock);
    
    return 0;
  }
}