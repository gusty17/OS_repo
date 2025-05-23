#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/fs.h"

// Helper function to extract only filename from a path
char* fmtname(char *path) {
  static char buf[DIRSIZ+1];
  char *p;

  // Find the last '/'
  for(p=path+strlen(path); p >= path && *p != '/'; p--);
  p++;

  // Return just the filename
  if(strlen(p) >= DIRSIZ)
    return p;
  memmove(buf, p, strlen(p)); // move p to buf
  buf[strlen(p)] = 0; //end buf with 0
  return buf;
}

// Recursive find function that opens path directory and reads each entry, if entry is file it checks if the name matches the target
void find(char *path, char *target) {
  //assume elpath kan asln /home/user
  char buf[512], *p;
  int fd;
  struct dirent de;// directory entry feha elname w
  struct stat st; // file status meta data about the file ex size,...

  // Open the directory
  if((fd = open(path, 0)) < 0){ // open with read only key
    printf("find: cannot open %s\n", path);
    return;
  }

  if(fstat(fd, &st) < 0){ // fstat bt2ole fd da directory wala file w t3melha store fe st
    printf("find: cannot stat %s\n", path);
    close(fd);
    return;
  }

  // If it's a file, check the name
  if(st.type != T_DIR){
    if(strcmp(fmtname(path), target) == 0){
      printf("%s\n", path);
    }
    close(fd);
    return;
  }

  // It's a directory; traverse it
  if(strlen(path) + 1 + DIRSIZ + 1 > sizeof(buf)){
    printf("find: path too long\n");
    close(fd);
    return;
  }

  strcpy(buf, path); // copy path to buf
  p = buf + strlen(buf);
  *p++ = '/'; //output  bta3 el satr da  p = /home/user/

  while(read(fd, &de, sizeof(de)) == sizeof(de)){
    if(de.inum == 0) // if inum = 0 means empty directory file/directory name = space " " -> de.inum == 0
      continue;

    // Skip "." and ".."
    // current and parent directories are skipped to avoid infinite loops
    if(strcmp(de.name, ".") == 0 || strcmp(de.name, "..") == 0)
      continue;

    memmove(p, de.name, DIRSIZ); //add name to p
    p[DIRSIZ] = 0; //end p with 0 (null)

    if(stat(buf, &st) < 0){
      printf("find: cannot stat %s\n", buf);
      continue;
    }
    // Recursively search
    find(buf, target);
  }
  close(fd);
}

int main(int argc, char *argv[]) {
  if (argc == 2 && strcmp(argv[1], "?") == 0) {
    printf("Usage: find <directory> <filename>\n");
    exit(0);
  }
  if(argc != 3){
    printf("invalid input\n");
    exit(1);
  }
  find(argv[1], argv[2]);
  exit(0);
}
