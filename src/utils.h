#ifndef __UTILS__
#define __UTILS__

template<class T>
void expand_array(T*& array, const int n, const int new_n) {
  T* new_array = new T[new_n];
  for (int i=0; i<n; i++) {
    new_array[i] = array[i];
  }
  delete array;
  array = new_array;
}

template<class T>
void expand_array(T*& array, const int length, const int new_n, T def) {
  T* new_array = new T[new_n];
  for (int i=0; i<length; i++) {
    new_array[i] = array[i];
  }
  for (int i=length; i<new_n; i++) {
    new_array[i] = def;
  }
  delete array;
  array = new_array;
}

#endif
