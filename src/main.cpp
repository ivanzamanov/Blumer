
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include "DAWG.h"
#include "hash.h"

using namespace std;

DAWG* buildDAWG(const int& fd);

int main(int argc, char** argv) {
  if(argc < 2) {
    printf("No input file specified\n");
    return 1;
  } else {
    int fd;
    fd = open(argv[1], O_RDONLY);
    DAWG* fda = buildDAWG(fd);
    int output = 0;
    for (int i=0; i<fda->last_state + 1; i++) {
      if(fda->types[i].field != 1)
        output++;
    }
//    printf("Total states = %d\n", fda->last_state + 1);
    printf("%d\n", output);
  }
}

DAWG* buildDAWG(const int& fd) {
  const int SIZE = 4096;
  unsigned char buf[SIZE];

  DAWG* fda = new DAWG;
  int current = fda->initial;
  int bytes = 1;
  struct stat st;
  fstat(fd, &st);
  fda->max_cap = st.st_size * 2;
  while(bytes > 0) {
    bytes = read(fd, buf, SIZE);
    for (int i=0; i<bytes; i++) {
      current = fda->update(current, buf[i]);
    }
  }

  return fda;
}
