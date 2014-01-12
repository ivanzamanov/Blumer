#include "hash.h"
#include <cstdint>

#ifndef __DAWG_H__
#define __DAWG_H__

using namespace std;

const int MAX_CHAR = 26;
#pragma pack(push,1)
struct V_Type {
  V_Type() {
    field = 0;
  }
  uint8_t field:2;
};
#pragma pack(pop)
typedef V_Type val_type;

class DAWG {
public:
  DAWG();

  int* length;
  int* slink;
  val_type* types;
  
  int initial;
  int states_c;
  int last_state;
  int max_cap = -1;
  int output_count = 0;

  void** trans;

  ~DAWG() {
    for (int i=0; i<states_c; i++) {
      if(types[i].field == 2)
        delete (hash<int>*)trans[i];
    }
    delete types;
    delete length;
    delete slink;
    delete trans;
  }

  int update(int current, unsigned char a);

private:
  void expand();
  int new_state();
  int split(int state, unsigned char c);
  int get_trans(int from, unsigned char ch);
  int build_state(int parent, unsigned char ch);
  void set_trans(int from, unsigned char ch, int to);
  void copy_trans(int dest, int src);
  
};

#endif
