#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

//factorial function
int main(int argc, char *argv[])
{
  if(argc == 2 && strcmp(argv[1], "?") == 0) {
    printf("Usage: calc factorial of input number.\n");
    exit(0);
  }
  if(argc != 2) {
    printf("You can only enter one number \n");
    exit(0);
  }
  int num = atoi(argv[1]);
  int fact = 1 ;
  if (num < 0 )
    printf("invalid number \n");
  else {
    for (int i = 1 ; i <= num;i++ ){
      fact *= i ;
    }
    printf("The factorial of %d is %d\n", num,fact);
  }
  exit (0);
}
