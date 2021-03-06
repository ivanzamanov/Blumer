
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
  hash<int> h;
  unsigned char ch = MAX_CHAR;
  for (int i=MAX_CHAR; i <= 2*MAX_CHAR; i++) {
    h.insert(ch, i);
    ch++;
  }
  ch = 0;
  for (int i=0; i<=3 * MAX_CHAR; i++) {
    printf("%d\n", h.get(ch, -1));
    ch++;
  }
    printf("Table size = %d, cap = %d\n", h.size, h.cap);
  if(argc < 2) {
    printf("No input file specified\n");
    return 1;
  } else {
    int fd;
    fd = open(argv[1], O_RDONLY);
    DAWG* fda = buildDAWG(fd);
    int total = 0;
    for(int i=0; i<fda->last_state+1; i++) {
      int count = 0;
      for (int j = 0; j<MAX_CHAR; j++) {
        if(fda->trans[i][j] != -1) 
          count++;
      }
      if(count != 1)
        total++;
    }
    printf("Total states = %d\n", fda->last_state + 1);
    printf("Output states = %d\n", total);
  }
}

DAWG* buildDAWG(const int& fd) {
  const int SIZE = 4096;
  unsigned char buf[SIZE];

  DAWG* fda = new DAWG;
  int current = fda->initial;
  int bytes = 1;
  while(bytes > 0) {
    bytes = read(fd, buf, SIZE);
    for (int i=0; i<bytes; i++) {
      current = fda->update(current, buf[i] - 97);
    }  
  }

  return fda;
}
