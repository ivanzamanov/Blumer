#include "DAWG.h"
#include "utils.h"

#include <stdio.h>

DAWG::DAWG() {
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

const double factor = 1.5;
void DAWG::expand() {
  DAWG& dawg = *this;
  int new_c = ((double) dawg.states_c) * factor;
  expand_array(dawg.length, dawg.states_c, new_c);
  expand_array(dawg.slink, dawg.states_c, new_c);
  printf("New length = %d\n", new_c);
  int (*new_trans)[MAX_CHAR] = new int[new_c][MAX_CHAR];
  for (int i = 0; i < dawg.states_c; i++) {
    copy_array(dawg.trans[i], new_trans[i], MAX_CHAR);
  }
  delete dawg.trans;
  dawg.trans = new_trans;
  for (int i = dawg.states_c; i < new_c; i++) {
    fill_array(dawg.trans[i], MAX_CHAR, -1);
  }
  dawg.states_c = new_c;
}

int DAWG::new_state() {
  int result = this->last_state + 1;
  if(result == this->states_c) {
    this->expand();
  }
  this->last_state = result;
  return result;
}

int DAWG::update(int current, char a) {
  DAWG& fda = *this;
  int b = (int) a;
  int n_state = fda.new_state();
  fda.length[n_state] = fda.length[current] + 1;
  fda.trans[current][b] = n_state;
  
  int t = -1, suffix_state = current;
  while (suffix_state != fda.initial && t == -1) {
    suffix_state = fda.slink[suffix_state];
    int next = fda.trans[suffix_state][b];
    if (next < 0) {
      fda.trans[suffix_state][b] = n_state;
    } else if (fda.length[suffix_state] + 1 == fda.length[next]) {
      t = next;
    } else {
      t = split(suffix_state, a);
    }
  }

  if (t == -1) {
    t = fda.initial;
  }

  fda.slink[n_state] = t;
  return n_state;
}

int DAWG::split(int state, char c) {
  DAWG& fda = *this;
  int a = (int) c;
  int r = fda.trans[state][a];
  int n = fda.new_state();
  fda.length[n] = fda.length[state] + 1;
  fda.trans[state][a] = n;

  for (int i=0; i<MAX_CHAR; i++) {
    fda.trans[n][i] = fda.trans[r][i];
  }
  fda.slink[n] = fda.slink[r];
  fda.slink[r] = n;

  int u = state;
  while (u != fda.initial) {
    u = fda.slink[u];
    if (fda.trans[u][a] == r) {
      fda.trans[u][a] = n;
    } else {
      break;
    }
  }
  return n;
}

