
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include "DAWG.h"
#include "hash.h"

using namespace std;

/*void test(int key, int val, hash<int>& h);

int main(int argc, char** argv) {
  hash<int> h;
  unsigned char ch = 0;
  const int MAX = 64;
  for (int i=MAX; i>0; i--) {
    test(ch * 2, i, h);
    test(ch, i, h);
    ch++;
  }
  ch=0;
  for (int i=0; i<MAX; i++) {
    test(ch * 2, i, h);
    ch++;
  }
  ch=0;
  for (int i=0; i<MAX; i++) {
    printf("%d \n", h.get(ch, -1));
    ch++;
  }
  return 0;
}

void test(int key, int val, hash<int>& h) {
  h.insert(key, val);
  int res = h.get(key, -1);
  if(res != val) {
    printf("res = %d ch = %d i = %d\n", res, key, val);
  }
}
*/

int main() {
  unsigned long int n_key = 0xFF;
  unsigned long int n_val = 0xFE;
  unsigned long int encoded = encode(n_key, n_val);
  printf("%X\n", encoded);
  unsigned long int key = get_key(encoded);
  printf("%X\n", key);
  unsigned long int val = get_value(encoded);
  printf("%X\n", val);
  return 0;
}