#include "DAWG.h"
#include "utils.h"

DAWG::DAWG() {
  length = new int[2];
  fill_array(length, 2, -1);
  slink = new int[2];
  fill_array(slink, 2, -1);
  types = new val_type[2];
  types[0].field = 0;
  types[1].field = 0;
  
  initial = 0;
  states_c = 2;
  last_state = 0;
  output_count = 1;

  trans = new void*[2];
  trans[0] = 0;
  trans[1] = 0;
}

const double factor = 2;
void DAWG::expand() {
  DAWG& fda = *this;
  int new_c = ((double) fda.states_c) * factor;
  if(max_cap >= 10 && new_c > max_cap) {
    new_c = max_cap;
  }
  expand_array(fda.length, fda.states_c, new_c);
  expand_array(fda.slink, fda.states_c, new_c);
  expand_array(fda.types, fda.states_c, new_c);
  void **new_trans = new void*[new_c];
  for (int i = 0; i < fda.states_c; i++) {
    new_trans[i] = fda.trans[i];
  }
  delete fda.trans;
  fda.trans = new_trans;
  fda.states_c = new_c;
}

int DAWG::new_state() {
  int result = this->last_state + 1;
  if(result == this->states_c) {
    this->expand();
  }
  types[result].field = 0;
  trans[result] = 0;
  output_count++;
  this->last_state = result;
  return result;
}

int DAWG::build_state(int parent, unsigned char ch) {
  DAWG& fda = *this;
  int n_state = fda.new_state();
  fda.length[n_state] = fda.length[parent] + 1;
  fda.set_trans(parent, ch, n_state);
  return n_state;
}

int DAWG::update(int current, unsigned char a) {
  DAWG& fda = *this;
  int n_state = build_state(current, a);

  int t = -1, suffix_state = current;
  while (suffix_state != fda.initial && t == -1) {
    suffix_state = fda.slink[suffix_state];
    int next = fda.get_trans(suffix_state, a);
    if (next < 0) {
      fda.set_trans(suffix_state, a, n_state);
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

int DAWG::split(int state, unsigned char c) {
  DAWG& fda = *this;
  int r = fda.get_trans(state, c);
  int n = fda.build_state(state, c);

  fda.copy_trans(n, r);
  fda.slink[n] = fda.slink[r];
  fda.slink[r] = n;

  int u = state;
  while (u != fda.initial) {
    u = fda.slink[u];
    if(fda.get_trans(u, c) == r) {
      fda.set_trans(u, c, n);
    } else {
      break;
    }
  }
  return n;
}

unsigned long int encode(unsigned char c, int i) {
  return (((unsigned long int) c) << 56) + i;
}

int get_value(long unsigned int a) {
  return a & (0x00FFFFFFFFFFFFFF);
}

unsigned char get_key(long unsigned int a) {
  return (unsigned char) (a >> 56);
}

int DAWG::get_trans(int from, unsigned char ch) {
  if(types[from].field == 0)
    return -1;
  else if(types[from].field == 1) {
    unsigned char c = get_key((unsigned long int)trans[from]);
    if(c == ch)
      return get_value((unsigned long int)trans[from]);
    else
      return -1;
  }
  else if(types[from].field == 2)
    return ((hash<int>*)trans[from])->get(ch, -1);
  throw 1;
}

void DAWG::set_trans(int from, unsigned char ch, int to) {
  if(types[from].field == 0) {
    trans[from] = (void*) encode(ch, to);
    output_count--;
    types[from].field = 1;
  } else if(types[from].field == 1) {
    unsigned char key = get_key((unsigned long int)trans[from]);
    if(key == ch) {
      trans[from] = (void*) encode(key, to);
      return;
    } else {
      unsigned long int val = get_value((unsigned long int)trans[from]);
      hash<int>* h = new hash<int>();
      h->insert(key, val);
      h->insert(ch, to);
      trans[from] = h;
      
      types[from].field = 2;
      output_count++;
    }
  } else {
    ((hash<int>*)trans[from])->insert(ch, to);
  }
  if(get_trans(from, ch) != to)
    throw 1;
}

void DAWG::copy_trans(int dest, int src) {
  if(types[dest].field == 2) {
    delete (hash<int>*)trans[dest];
  }
  int old_type = types[dest].field;
  types[dest].field = types[src].field;
  if(types[dest].field == 2) {
    trans[dest] = new hash<int>( *(hash<int>*) trans[src] );
  } else
    trans[dest] = trans[src];

  if(old_type != types[dest].field) {
    if(old_type == 1)
      output_count--;
    else
      output_count++;
  }
}
