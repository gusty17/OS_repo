#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/fcntl.h"                                                   		// for O_CREATE and O_EXCL

int
main(int argc, char *argv[])
{
  if(argc == 2 && strcmp(argv[1], "?") == 0) {
    printf("Usage: create file \n");
    exit(0);
  }

  if(argc != 2){
    printf("You need to have 2 paramters: cp fd  \n");
    exit(1);
  }

  int fd = open(argv[1],O_CREATE|O_RDWR);// create file if it doesn't exist or fail if the file already exists or open for read writing

  if(fd < 0){                                                              		// negative value means file already exists or there's an error
    printf("touch: file %s cannot be created\n", argv[1]);
    exit(1);
  }

  printf("file opened successful \n");
  close(fd);
  exit(0);                                                                  		//the file was created successfully, it closes the file and exits normally.

}
