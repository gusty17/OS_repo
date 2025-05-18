#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/fcntl.h"     // for O_CREATE and O_EXCL

//copy function
int main(int argc, char *argv[])
{
  if(argc == 2 && strcmp(argv[1], "?") == 0) {
    printf("Usage: copy data from fd1 to fd2. \n");
    exit(0);
  }

  if(argc != 3) {
    printf("You need to have 3 paramters: cp fd1 fd2 \n");
    exit(0);
  }

  int fd1 = open (argv[1], O_RDONLY); // open file 1 with read only key

  if (fd1 < 0){
    printf ("file descriptor 1 is invalid \n");
    exit (0);
  }

  int fd2 = open (argv[2], O_WRONLY); // open file 2 with create/read/write key
  if (fd2 < 0) {
    printf("file descriptor 2 is invalid \n");
  }

  char buffer [500];
  int n ;
  //read up to (sizeof buffer) bytes from the fd into buf,return number of bytes
  while ((n = read(fd1,buffer, sizeof (buffer)))> 0){
    write (fd2, buffer , n ); //write n byte from buf to the fd, return number of bytes
  }
  printf("successful copy,content of fd1 copied to fd2 \n");
  close (fd1);
  close (fd2);
  exit(0);
}
