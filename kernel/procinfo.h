#include "types.h"
// for get proc table
struct process_info {
  int pid;
  int ppid;
  int state;
  char name[16];
  uint64 sz;  //memory size
};
