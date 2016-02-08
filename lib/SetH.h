#ifndef SETH_H
#define SETH_H

#include "MapH.h"

template<class T>
class Set {
 public:
  Set();
  ~Set();
  Set(const Set<T> &other);
  const Set<T>& operator=(const Set<T>& other);
  class Iterator {
  public:
    Iterator(); 
    T operator*() const;
    Set<T>::Iterator operator++();
    Set<T>::Iterator operator++(int dummy);
    Set<T>::Iterator operator=(const Set<T>::Iterator& other);
    bool operator==(const Set<T>::Iterator& other) const;
    bool operator!=(const Set<T>::Iterator& other) const;
    friend class Set;
  private:
    Iterator(const typename Map<T, T>::Iterator mi);
    typename Map<T, T>::Iterator internalIterator;
  };
  Set<T>::Iterator begin() const;
  Set<T>::Iterator end() const;
  const int size() const;
  void add(const T& item);
  void remove(const T& item);
  const bool contains(const T& item) const;
  void merge(const Set<T>& other);
  Set<T> setUnion(const Set<T>& other) const;
  Set<T> setIntersection(const Set<T>& other) const;
  void print();
  void printHT();
 private:
  Map<T, T> internalStorage;
};

#include "SetCPP.h"

#endif
