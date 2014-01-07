#ifndef __UTILS__
#define __UTILS__

template<class T>
inline void expand_array(T*& array, const int n, const int new_n) {
  T* new_array = new T[new_n];
  for (int i=0; i<n; i++) {
    new_array[i] = array[i];
  }
  delete array;
  array = new_array;
}

template<class T>
inline void expand_array(T*& array, const int length, const int new_n, T def) {
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

template<class T>
inline void fill_array(T* array, const int length, const T& value) {
  for (int i = 0; i < length; i++) {
    array[i] = value;
  }
}

template<class T>
inline void copy_array(T* from, T* to, const int length) {
  for (int i = 0; i < length; i++) {
    to[i] = from[i];
  }
}

#endif
