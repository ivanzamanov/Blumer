#include "hash.h"

#ifndef __DAWG_H__
#define __DAWG_H__


const int MAX_CHAR = 26;
class DAWG {
public:
  DAWG();

  int* length;
  int* slink;
  int initial;
  int states_c;
  int last_state;

  hash<int> **trans;

  ~DAWG() {
    delete length;
    delete slink;
    delete trans;
  }

  int update(int current, char a);

private:
  void expand();
  int new_state();
  int split(int state, char c);
  int get_trans(int from, unsigned char ch);
  void set_trans(int from, unsigned char ch, int to);
  void copy_trans(int dest, int src);
  
};

#endif
