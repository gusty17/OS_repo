#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/fcntl.h"

int main(int argc, char *argv[])
{
  if(argc == 2 && strcmp(argv[1], "?") == 0) {
    printf("Usage: mv source destination\n");
    exit(0);
  }

  if (argc != 3) {
    printf("unvalid paramaters \n");
    exit(0);
  }
  //rename aktr mn 2nha move w sa2lt feha hima 2ale hwa 3ayz keda
  char *src = argv[1];
  char *dst = argv[2];

  // Create hard link
  if (link(src, dst) < 0) { // src w dst byshwro 3ala nafs el file dlw2ty
    printf("Error: Cannot link %s to %s. Source may not exist or destination already exists.\n", src, dst);
    exit(0);
  }

  // Remove original file
  if (unlink(src) < 0) {
    printf("Error: Cannot unlink %s. Removing destination.\n", src);
    unlink(dst);
    exit(0);
  }

  printf("Moved/renamed '%s' to '%s'\n", src, dst);
  exit(0);
}
