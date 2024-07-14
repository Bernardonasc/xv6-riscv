#ifndef _PSTAT_H_
#define _PSTAT_H_

#include "param.h"
#include "defs.h"

struct pstat {
  char name[NPROC][16];        // name of the process
  enum procstate state[NPROC]; // state of the process   
  int inuse[NPROC];            // whether this slot of the process table is in use (1 or 0)
  int tickets[NPROC];          // the number of tickets this process has
  int pid[NPROC];              // the PID of each process
  int ticks[NPROC];            // the number of ticks each process has accumulated 
};

#endif // _PSTAT_H_