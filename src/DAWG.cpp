#include "DAWG.h"
#include "utils.h"

#include <stdio.h>

DAWG::DAWG() {
  length = new int[2];
  fill_array(length, 2, -1);
  slink = new int[2];
  fill_array(slink, 2, -1);
  initial = 0;
  states_c = 2;
  last_state = 0;

//  trans = new int[2][MAX_CHAR];
//  fill_array(trans[0], MAX_CHAR, -1);
//  fill_array(trans[1], MAX_CHAR, -1);
  trans = new hash<int>*[2];
  trans[0] = new hash<int>();
  trans[1] = new hash<int>();
}

const double factor = 1.5;
void DAWG::expand() {
  DAWG& dawg = *this;
  double tr = 0;
  double sizes = 0;
  for (int i=0; i<=last_state; i++) {
    tr += dawg.trans[i]->size;
    sizes += dawg.trans[i]->cap;
  }
//  printf("Trans = %f, Size = %f\n", tr/last_state, sizes/last_state);
  int new_c = ((double) dawg.states_c) * factor;
  expand_array(dawg.length, dawg.states_c, new_c);
  expand_array(dawg.slink, dawg.states_c, new_c);
  printf("New length = %d\n", new_c);
//  int (*new_trans)[MAX_CHAR] = new int[new_c][MAX_CHAR];
  hash<int> **new_trans = new hash<int>*[new_c];
  for (int i = 0; i < dawg.states_c; i++) {
//    copy_array(dawg.trans[i], new_trans[i], MAX_CHAR);
    new_trans[i] = dawg.trans[i];
  }
  delete dawg.trans;
  dawg.trans = new_trans;
//  for (int i = dawg.states_c; i < new_c; i++) {
//    fill_array(dawg.trans[i], MAX_CHAR, -1);
//  }
  dawg.states_c = new_c;
}

int DAWG::new_state() {
  int result = this->last_state + 1;
  if(result == this->states_c) {
    this->expand();
  }
  trans[result] = new hash<int>();
  this->last_state = result;
  return result;
}

int DAWG::update(int current, char a) {
  DAWG& fda = *this;
  int b = (int) a;
  int n_state = fda.new_state();
  fda.length[n_state] = fda.length[current] + 1;
  fda.set_trans(current, b, n_state);
  
  int t = -1, suffix_state = current;
  while (suffix_state != fda.initial && t == -1) {
    suffix_state = fda.slink[suffix_state];
    int next = fda.get_trans(suffix_state, b);
    if (next < 0) {
      fda.set_trans(suffix_state, b, n_state);
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
  int r = fda.get_trans(state, a);
  int n = fda.new_state();
  fda.length[n] = fda.length[state] + 1;
  fda.set_trans(state, a, n);

  fda.copy_trans(n, r);
  fda.slink[n] = fda.slink[r];
  fda.slink[r] = n;

  int u = state;
  while (u != fda.initial) {
    u = fda.slink[u];
    if(fda.get_trans(u, a) == r) {
      fda.set_trans(u, a, n);
    } else {
      break;
    }
  }
  return n;
}

int DAWG::get_trans(int from, unsigned char ch) {
  return trans[from]->get(ch, -1);
}

void DAWG::set_trans(int from, unsigned char ch, int to) {
  trans[from]->insert(ch, to);
}

void DAWG::copy_trans(int dest, int src) {
  delete trans[dest];
  trans[dest] = new hash<int>(*trans[src]);
//  for (int i=0; i<MAX_CHAR; i++) {
//    trans[dest][i] = trans[src][i];
//  }
}
