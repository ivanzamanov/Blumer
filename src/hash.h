#include "utils.h"

#ifndef __HASH_H__
#define __HASH_H__

const int P = 53;
const int C = 50;
const double LOAD_FACTOR = 0.8d;
const int MAX_CAP = 32;

typedef char hash_key_t;

template<class T>
class hash {
public:
  hash();
  hash(const hash<T>& other);

  int cap;
  int size;

  void insert(const hash_key_t& key, const T& data);
  const T& get(const hash_key_t& key, const T& def);

private:
  void expand();
  int get_hash(const hash_key_t& key, const int& i);

  T* data;
  hash_key_t* keys;
};

template<class T>
hash<T>::hash() {
  hash<T>& h = *this;
  h.cap = 1;
  h.size = 0;
  h.keys = new hash_key_t[cap];
  for (int i=0; i<cap; i++) {
    h.keys[i] = -1;
  }
  h.data = new T[cap];
}

template<class T>
hash<T>::hash(const hash<T>& other) {
  hash<T>& h = *this;
  h.cap = other.cap;
  h.size = other.size;
  h.keys = new hash_key_t[cap];
  h.data = new T[cap];
  for (int i=0; i<size; i++) {
    h.keys[i] = other.keys[i];
    h.data[i] = other.data[i];
  }
}

template<class T>
void hash<T>::insert(const hash_key_t& key, const T& el) {
  int index = bin_search(keys, size, key);
  if(index >= 0) {
    this->data[index] = el;
  } else {
    if(size >= cap)
      expand();
    index = -index - 1;
    for (int i = size; i > index; i--) {
      keys[i] = keys[i-1];
      data[i] = data[i-1];
    }
    keys[index] = key;
    data[index] = el;
    size++;
  }
}

template<class T>
const T& hash<T>::get(const hash_key_t& key, const T& def) {
  int index = bin_search(keys, size, key);
  if(index >= 0)
    return data[index];
  
  return def;
}

template<class T>
int hash<T>::get_hash(const hash_key_t& key, const int& i) {
  return ((C * key) % P + i) % this->cap;
}

template<class T>
void hash<T>::expand() {
  hash<T>& table = *this;
  int new_c = table.cap + 1;
  expand_array(table.keys, table.cap, new_c);
  expand_array(table.data, table.cap, new_c);
  table.cap = new_c;
}

#endif
