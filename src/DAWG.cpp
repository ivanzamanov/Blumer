#include "utils.h"
#include "DAWG.h"

#include <stdio.h>

const double factor = 1.5;
void expandDAWG(DAWG& dawg) {
  int new_c = ((double) dawg.states_c) * factor;
  expand_array(dawg.length, dawg.states_c, new_c);
  expand_array(dawg.slink, dawg.states_c, new_c);
  printf("New length = %d\n", new_c);
  int (*new_trans)[MAX_CHAR] = new int[new_c][MAX_CHAR];
  for (int i=0; i<dawg.states_c; i++) {
    for (int j = 0; j<MAX_CHAR; j++) {
      new_trans[i][j] = dawg.trans[i][j];
    } 
  }
  delete dawg.trans;
  dawg.trans = new_trans;
  for (int i=dawg.states_c; i<new_c; i++) {
    for (int j = 0; j<MAX_CHAR; j++) {
      dawg.trans[i][j] = -1;
    } 
  }
  dawg.states_c = new_c;
}

int new_state(DAWG& fda) {
  int result = fda.last_state + 1;
  if(result == fda.states_c) {
    expandDAWG(fda);
  }
  fda.last_state = result;
  return result;
}

int update(DAWG& fda, int current, char c);
int split(DAWG& fda, int state, char c);

int hit = 0;
int update_DAWG(DAWG& fda, int current, char a) {
  int b = (int) a;
  int n_state = new_state(fda);
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
      t = split(fda, suffix_state, a);
    }
  }

  if (t == -1) {
    t = fda.initial;
  }

  fda.slink[n_state] = t;
  return n_state;
}

int split(DAWG& fda, int state, char c) {
  int a = (int) c;
  int r = fda.trans[state][a];
  int n = new_state(fda);
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

