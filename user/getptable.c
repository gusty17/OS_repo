#include "kernel/types.h"
#include "user/user.h"
#include "kernel/procinfo.h"

enum procstate {UNUSED,USED,SLEEPING,RUNNABLE,RUNNING,ZOMBIE,NSTATES};
static const char *statename[NSTATES] = {
  [UNUSED]    = "unused",
  [USED]      = "used",
  [SLEEPING]  = "sleep ",
  [RUNNABLE]  = "runble(ready)",
  [RUNNING]   = "running ",
  [ZOMBIE]    = "zombie",
  };

int main(int argc, char *argv[]) {
  if(argc == 2 && strcmp(argv[1], "?") == 0) {
    printf("Usage: show proccess table.\n");
    exit(0);
  }
  if(argc != 1) {
    printf("invalid input\n");
    exit(0);
  }
  struct process_info ptable[64];
  int n = getptable(64, ptable);
  for (int i = 0; i < n; i++) {
      printf("PID:%d    PPID:%d      NAME:%s       SIZE:%ld    STATE:%s\n",
            ptable[i].pid, ptable[i].ppid, ptable[i].name, ptable[i].sz,statename[ptable[i].state]);
  }
  exit(0);
}
