#include "types.h"

extern int kbdint_count; // in console.c
extern int syscall_counter; //in syscall.c
//static uint64 seed = 1;

uint64
sys_kbdint(void) {
  return kbdint_count;
}

uint64
sys_countsyscall(void) {
  return syscall_counter ;
}
/*uint64 sys_random(void){
  seed = (1664525 * seed + 1013904223);
  return (int)(seed & 0x7fffffff);
}
*/
