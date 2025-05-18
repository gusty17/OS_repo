#include "kernel/types.h"
#include "user/user.h"
#include "kernel/stat.h"

int
main(int argc, char *argv[])
{
  if(argc == 2 && strcmp(argv[1], "?") == 0) {
    printf("Usage: show how many key user pressed.\n");
    exit(0);
  }
  if(argc != 1) {
    printf("invalid input\n");
    exit(0);
  }
  printf("Keyboard ints = %d\n", kbdint());
}
