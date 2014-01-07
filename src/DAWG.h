#ifndef __DAWG_H__
#define __DAWG_H__

const int MAX_CHAR = 26;
class DAWG {
public:
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

  int update(int current, char a);

private:
  void expand();
  int new_state();
  int split(int state, char c);
  
};

int new_state(const DAWG& dawg);
int update_DAWG(DAWG& fda, int current, char a);

#endif
