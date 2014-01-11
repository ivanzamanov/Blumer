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

  int cap = 4;
  int size = 0;

  void insert(const hash_key_t& key, const T& data);
  const T& get(const hash_key_t& key, const T& def);

private:
  void expand();
  int get_hash(const hash_key_t& key, const int& i);

  int limit = 4;

  T* data;
  hash_key_t* keys;
};

template<class T>
hash<T>::hash() {
  hash<T>& h = *this;
  h.cap = 4;
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
  for (int i=0; i<cap; i++) {
    h.keys[i] = other.keys[i];
    h.data[i] = other.data[i];
  }
}

template<class T>
void hash<T>::insert(const hash_key_t& key, const T& data) {
  size++;
  if(size >= cap * LOAD_FACTOR) {
    expand();
  }
  int i = 0;
  while(i <= limit) {
    int h = get_hash(key, i);
    hash_key_t& current = keys[h];
    if(current == -1 || current == key) {
      current = key;
      this->data[h] = data;
      return;
    }
    i++;
  }
  expand();
  size--;
  insert(key, data);
}

template<class T>
const T& hash<T>::get(const hash_key_t& key, const T& def) {
  int i = 0;
  while(i <= limit) {
    int h = get_hash(key, i);
    hash_key_t& current = keys[h];
    if(current == key) {
      return data[h];
    } else if(current == -1) {
      return def;
    }
    i++;
  }
  return def;
}

template<class T>
int hash<T>::get_hash(const hash_key_t& key, const int& i) {
  return ((C * key) % P + i) % this->cap;
}

template<class T>
void hash<T>::expand() {
  hash<T>& table = *this;
  if(table.cap == MAX_CAP) {
    return;
  }
  hash_key_t* old_table = table.keys;
  T* old_data = table.data;
  int old_cap = table.cap;
  table.cap = old_cap * 2;
  if(table.cap > MAX_CAP) {
    table.cap = MAX_CAP;
  }
  table.keys = new hash_key_t[table.cap];
  table.data = new T[table.cap];
  for(int i = 0; i < table.cap; i++) {
    table.keys[i] = -1;
  }
  table.size = 0;
  for (int i=0; i < old_cap; i++) {
    hash_key_t key = old_table[i];
    T& data = old_data[i];
    if(key >= 0) {
      table.insert(key, data);
    }
  }
  delete old_table;
  delete old_data;
  limit = cap;
}

#endif
