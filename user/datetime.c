#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/timeinfo.h" //rtcdate struct

int main(int argc, char *argv[])
 {
  if(argc == 2 && strcmp(argv[1], "?") == 0) {
    printf("Usage: show date and time.\n");
    exit(0);
  }
  if(argc != 1) {
    printf("invalid input\n");
    exit(0);
  }
  struct rtcdate r;
  if (datetime(&r) == 0) {
    printf("Current datetime: %d-%d-%d %d:%d:%d\n",
           r.year, r.month, r.day, r.hour, r.minute, r.second);
  }
  else {
    printf("datetime syscall failed\n");
  }
  exit(0);
}
