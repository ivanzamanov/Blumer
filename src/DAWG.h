#ifndef __DAWG_H__
#define __DAWG_H__

const int MAX_CHAR = 26;
struct DAWG {
  DAWG() {
    length = new int[2];
    length[0] = 0;
    length[1] = 1;
    slink = new int[2];
    slink[0] = -1;
    slink[1] = -1;
    trans = new int[2][MAX_CHAR];
    for (int i=0; i<MAX_CHAR; i++) {
      trans[0][i] = -1;
      trans[1][i] = -1;
    }
    initial = 0;
    states_c = 2;
    last_state = 0;
  }

  int* length;
  int* slink;
  int (*trans)[MAX_CHAR];
  int initial;

  int states_c;
  int last_state;

  ~DAWG() {
    delete length;
    delete slink;
    delete trans;
  }
};

void expandDAWG(const DAWG& dawg);
int new_state(const DAWG& dawg);
int update_DAWG(DAWG& fda, int current, char a);

#endif
