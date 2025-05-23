#include "types.h"
#include "riscv.h"
#include "defs.h"
#include "param.h"
#include "memlayout.h"
#include "spinlock.h"
#include "proc.h"
#include "timeinfo.h"

uint64
sys_exit(void)
{
  int n;
  argint(0, &n);
  exit(n);
  return 0;  // not reached
}

uint64 sys_getpid(void)
{
  return myproc()->pid;
}

// get parent pid
uint64 sys_getppid(void)
{
    struct proc *curproc = myproc(); //myproc () return a pointer to the current proc
    //->	Access member (parent) of struct that pointer (curproc) points to
    if (curproc->parent)
        return curproc->parent->pid;
    return -1; // return -1 if proc has no parent.
}

uint64 sys_getptable(void) {
  int max;
  uint64 buff;
  argint(0, &max);
  argaddr(1, &buff); // get the address of the buffer from the user and store it in buff (type uint64)

  return getptable(max,buff);
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
  if(n < 0)
    n = 0;
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
// for time
void unix_to_rtc(uint timestamp, struct rtcdate *r) {
  // 1) Split into days since epoch, and seconds‐within‐today
  uint days = timestamp / 86400;           // 86400 seconds in a day
  uint secs_of_day = timestamp % 86400;

  // 2) Extract hour, minute, second from secs_of_day
  r->hour   = secs_of_day / 3600;          // 3600 seconds per hour
  r->minute = (secs_of_day % 3600) / 60;   // leftover seconds → minutes
  r->second = secs_of_day % 60;            // leftover seconds

  // 3) Compute year by subtracting full years’ worth of days
  int year = 1970;
  while (1) {
    // true length of this year
    int days_in_year;
    if (year % 4 == 0 && (year % 100 != 0 || year % 400 == 0))
      days_in_year= 366;
    else
      days_in_year = 365;
    if (days < days_in_year)
      break;
    days -= days_in_year;
    year++;
  }
  r->year = year;

  // 4) Compute month and day-of-month
  static int month_days[12] =
    {31,28,31,30,31,30,31,31,30,31,30,31};
  // adjust February for leap years
  if ( (r->year % 4 == 0 && (r->year % 100 != 0 || r->year % 400 == 0)) )
    month_days[1] = 29;

  int month = 0;
  while (days >= month_days[month]) {
    days -= month_days[month];
    month++;
  }
  r->month = month + 1;    // convert 0–11 → 1–12
  r->day   = days + 1;     // convert 0–(n−1) → 1–n
}

extern uint ticks;
uint64 sys_datetime(void)
{
  uint64 user_addr;
  //user -> kernel
  argaddr(0, &user_addr) ; //btakhod pointer (&r) mn el user space w t3melo store fe variable asmo user_addr 3shan a3rf astghdemo fe elkernel
  int three_hour = 3 * 60 * 60;
  uint curr = (BOOT_EPOCH + three_hour) + (ticks / 10);
  struct rtcdate r;

  // Use a conversion function (see below)
  unix_to_rtc(curr, &r);
  //kernel -> user
  if (copyout(myproc()->pagetable, user_addr, (char *)&r, sizeof(r)) < 0) //copy r to user_addr (pointer to r from user space) w elsize of copy = sizeof(r)
    return -1; //failed copy
  return 0;
}

//random
#define LCG_A 1103515245
#define LCG_C 12345

int
sys_random(void)
{
  static uint64 seed;

  // Use ticks as the changing seed
  extern uint ticks;
  acquire(&tickslock);
  seed = ticks;
  release(&tickslock);

  // Apply LCG
  seed = seed * LCG_A + LCG_C;

  // Return number in range [0, 100]
  return (seed % 101);

  //return (int)(seed & 0x7fffffff);  // old

}
