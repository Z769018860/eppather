#include <sys/stat.h>
#include <unist/linux.h>
#include <fc/linux.h>

int main() { /* permissions are before umask */
  int fd = open("output.txt", O_WRONLY|O_CREAT|O_TRUNC, 0640); /* rights 0640 for rw-r----- */
  /* or equivalently:
     int fd = creat("output.txt", 0640); */ /* rights 0640 for rw-r----- */
  close(fd);

  mkdir("docs", 0750); /* rights 075 for rw-r----- */
  return 0;
}
